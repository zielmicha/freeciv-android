
if(!console) {
    console = {
        log: function() {}
    }
}

function get_url_params() {
    var query = location.search.substr(1)
    var data = query.split("&")
    var result = {}
    for(var i=0; i<data.length; i++) {
        var item = data[i].split("=")
        result[item[0]] = unescape(item[1])
    }
    return result
}

var url_params = get_url_params()
var ws_url = "ws://" + location.hostname + ":" + location.port + "/ws"
if(url_params.wsurl)
    ws_url = url_params.wsurl
var ws = new WebSocket(ws_url)

ws.onopen = function() {
    send_message({'type': 'init',
                  'search': location.search,
                  'hash': location.hash})
    send_message({'type': 'init_cache'})
}

var image_cache = {} // TODO: lru cache
var current_screen = null
var last_screen_id = 0
var last_screen_content = null
var animation_source
var animation_target
var animation_direction
var animation_progress = null
var canvas_ctx
var canvas
var animation_timer_id

function handle_screen(image, frame) {
    if(animation_progress == null && frame.allow_animation != 0) {
        if(last_screen_content != null && frame.id != last_screen_id) {
            start_animation(image, frame.allow_animation)
        }
    }
    last_screen_id = frame.id
    last_screen_content = image
    draw_all()
}

function draw_screen() {
    canvas_ctx.fillStyle = '#500'
    canvas_ctx.fill()
    if(animation_progress == null) {
        canvas_ctx.drawImage(last_screen_content, 0, 0)
    } else {
        var w = $('canvas')[0].width
        canvas_ctx.drawImage(animation_source, -animation_progress * w, 0)
        canvas_ctx.drawImage(animation_target, (1-animation_progress) * w, 0)
    }
}

function start_animation(target, direction) {
    console.log("start animation!")
    if(direction == 1) {
        animation_source = last_screen_content
        animation_target = target
        animation_progress = 0
    } else {
        animation_target = last_screen_content
        animation_source = target
        animation_progress = 1
    }
    animation_direction = direction
    animation_timer_id = setInterval(animation_timer, 30)
}

function animation_timer() {
    if(animation_progress != null) {
        animation_progress += 0.1 * animation_direction
        if(animation_progress > 1 || animation_progress < 0) {
            animation_progress = null
        }
        draw_all(true)
    } else {
        clearInterval(animation_timer_id)
    }
}

function draw_layer(image, frame) {
    if(image == null)
        return;
    if(drag_offsets[frame.id]) {
        frame.offset = drag_offsets[frame.id]
    }
    if(animation_progress == null) {
        // drawImage is like - if anything is out of range, draw nothing
        var offx = Math.max(0, frame.offset[0])
        var offy = Math.max(0, frame.offset[1])
        var negoffx = Math.min(0, frame.offset[0])
        var negoffy = Math.min(0, frame.offset[1])
        var w = frame.size[0]
        var h = frame.size[1]
        w += negoffx
        h += negoffy
        w = Math.min(w, image.width - offx)
        h = Math.min(h, image.height - offy)
        canvas_ctx.clearRect(frame.pos[0], frame.pos[1],
                            frame.size[0], frame.size[1])
        canvas_ctx.drawImage(image,
                             offx, offy,
                             w, h,
                             frame.pos[0] - negoffx, frame.pos[1] - negoffy,
                             w, h)
    }
}

function draw_all(force) {
    var layers_ready = true
    for(var key in layerlist) {
        if(layerlist[key].data && !layerlist[key].img)
            layers_ready = false
    }
    if(force || layers_ready) {
        clear_canvas()

        if(layerlist.map)
            tiles_draw()

        for(var key in layerlist) {
            draw_layer(layerlist[key].img, layerlist[key])
        }
        draw_screen()
    }
}

function clear_canvas() {
    canvas_ctx.fillStyle = 'rgba(0, 0, 0, 1)'
    canvas_ctx.clearRect(0, 0, canvas.width, canvas.height)
}

var drag_id
var drag_start
var drag_delta
var drag_delta_offset

var drag_offsets = {}

var layer_click_handlers = {}

function layers_mouse_event(name, pos, e) {
    if(name == 'MOUSEBUTTONDOWN') {
        for(var key in layerlist) {
            var l = layerlist[key]
            if(pos[0] > l.pos[0] && pos[1] > l.pos[1] &&
              pos[0] < l.pos[0] + l.size[0] && pos[1] < l.pos[1] + l.size[1] ) {
                drag_id = l.layerid
                drag_start = pos
                drag_delta = [0, 0]
                if(!drag_offsets[drag_id])
                    drag_offsets[drag_id] = [0, 0]
                drag_delta_offset = drag_offsets[drag_id]
                return false
            }
        }
    } else if(name == 'MOUSEMOTION' && drag_start) {
        drag_delta = [pos[0] - drag_start[0] + drag_delta_offset[0],
                      pos[1] - drag_start[1] + drag_delta_offset[1]]
        drag_offsets[drag_id] = [
            drag_delta[0],
            drag_delta[1]
        ]
        draw_all()
        return false
    } else if(name == 'MOUSEBUTTONUP') {
        var result = drag_id
        drag_id = null
        if(result) {
            if(Math.abs(drag_delta[0]) + Math.abs(drag_delta[1]) < 6) {
                if(layer_click_handlers[result]) {
                    layer_click_handlers[result](e, pos)
                } else {
                    pass_mouse_event('MOUSEBUTTONDOWN', e)
                    pass_mouse_event('MOUSEBUTTONUP', e)
                }
            }
            return false
        }
    }
}

var layerlist = {}

ws.onmessage = function (evt) {
    var received_msg = evt.data
    var all_msg = JSON.parse(received_msg)
    var msg = []
    for(var i=0; i<all_msg.length; i++) {
        var m = all_msg[i]
        if(m.type == 'layer' || m.type == 'frame')
            msg.push(m)
        else if(m.type == 'tile') {
            tiles_process_message(m)
        } else if(m.type == 'tiles_center_at')
            tiles_center_at(m.pos)
        else if(m.type == 'tile_config')
            tiles_got_config(m)
    }
    load_image_cached(msg[0].data, function(img) {
        handle_screen(img, msg[0])
    })
    var finished = 0
    layerlist = {}
    var debugarea = $('.debugarea')
    debugarea.html('')
    for(var i=0; i<msg.length; i++) {
        if(!msg[i].data) continue;
        image_show_debug(msg[i].data)
    }
    for(var i=1; i<msg.length; i++) {
        layerlist[msg[i].layerid] = msg[i];
        if(!msg[i].data) {
            // fully transparent layer
            finished ++
            continue
        }
        (function(j) {
            load_image_cached(msg[i].data, function(img) {
                msg[j].img = img
                finished ++
                if(finished == msg.length - 1) draw_all()
            })
        })(i)
    }
};

function image_show_debug(data) {
    var debugarea = $('.debugarea')
    var c = $('<div>')
    $('<img height=100>').attr(
        'src', get_image_cached(data)).appendTo(c)
    $('<span>').text(parseInt(data.length / 1024) + 'kB').appendTo(c)
    c.appendTo(debugarea)
}

function load_image_cached(val, func) {
    return load_image_from_b64(get_image_cached(val), func)
}

function get_image_cached(val) {
    if(val[0] == 'get_from_cache') {
        return image_cache[val[1]]
    } else if(val[0] == 'store_to_cache') {
        image_cache[val[1]] = val[2]
        return val[2]
    } else {
        console.log('unknown cached image', val)
    }
}

function load_image_from_b64(b64, func) {
    var url = b64
    var img = new Image()
    img.src = url
    img.onload = function() {
        func(img)
    }
}

// events

var is_down = false

$(function() {
    canvas = $('#screen')[0]
    canvas_ctx = canvas.getContext('2d')

    $('#screen').mousedown(function(e) {
        is_down = true
        mouse_event('MOUSEBUTTONDOWN', e)
        return false
    }).mouseup(function(e) {
        is_down = false
        mouse_event('MOUSEBUTTONUP', e)
        return false
    }).mousemove(function(e) {
        if(is_down)
            mouse_event('MOUSEMOTION', e)
    }).contextmenu(function(e) {
        return false
    })
    $('body').keydown(function(e) {
        key_event('KEYDOWN', e)
    }).keyup(function(e) {
        key_event('KEYUP', e)
    })
})

function mouse_event(name, e) {
    var pos = [e.offsetX, e.offsetY]
    if(layers_mouse_event(name, pos, e) === false)
        return
    pass_mouse_event(name, e)
}

function pass_mouse_event(name, e) {
    var pos = [e.offsetX, e.offsetY]
    var button = e.button
    if(button == 2) button = 1
    func = name == 'MOUSEMOTION' ? send_throttled_message : send_message
    func({'type': name,
          'pos': pos,
          'button': button,
          'data': e.data})
}

function key_event(name, e) {
    send_message({'type': name,
                  'key': e.keyCode})
}

var last_message = {}

function send_throttled_message(msg) {
    var type = msg.type
    if(typeof last_message[type] == 'undefined') last_message[type] = 0
    if(new Date - last_message[type] > 100) {
        send_message(msg)
        last_message[type] = new Date
    }
}

function send_message(msg) {
    console.log(msg)
    ws.send(JSON.stringify(msg))
}

ws.onclose = function()
{
    console.log("Connection is closed...");
};
