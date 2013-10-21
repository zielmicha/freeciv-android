
var ws = new WebSocket("ws://" + location.hostname + ":" + location.port + "/ws")
ws.onopen = function() {}

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
    if(dragging_layer == frame.layerid) {
        frame.offset[0] = drag_start_pos[0] - drag_delta[0]
        frame.offset[1] = drag_start_pos[1] - drag_delta[1]
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
        if(!layerlist[key].img)
            layers_ready = false
    }
    if(force || layers_ready) {
        clear_canvas()
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

var dragging_layer
var drag_start
var drag_delta
var drag_start_pos

function layers_mouse_event(name, pos) {
    if(name == 'MOUSEBUTTONDOWN') {
        for(var key in layerlist) {
            var l = layerlist[key]
            if(pos[0] > l.pos[0] && pos[1] > l.pos[1] &&
              pos[0] < l.pos[0] + l.size[0] && pos[1] < l.pos[1] + l.size[1] ) {
                dragging_layer = l.layerid
                drag_start = pos
                drag_start_pos = [l.offset[0], l.offset[1]]
            }
        }
    } else if(name == 'MOUSEMOTION') {
        drag_delta = [pos[0] - drag_start[0],
                      pos[1] - drag_start[1]]
        draw_all()
    } else if(name == 'MOUSEBUTTONUP') {
        dragging_layer = null
    }
}

var layerlist = {}

ws.onmessage = function (evt) {
    var received_msg = evt.data
    msg = JSON.parse(received_msg)
    load_image_from_b64(msg[0].data, function(img) {
        handle_screen(img, msg[0])
    })
    var finished = 0
    layerlist = {}
    for(var i=1; i<msg.length; i++) {
        layerlist[msg[i].layerid] = msg[i];
        (function(j) {
            load_image_from_b64(msg[i].data, function(img) {
                msg[j].img = img
                finished ++
                if(finished == msg.length - 1) draw_all()
            })
        })(i)
    }
};

function load_image_from_b64(b64, func) {
    var url = 'data:image/png;base64,' + b64
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
    layers_mouse_event(name, pos)
    var button = e.button
    if(button == 2) button = 1
    func = name == 'MOUSEMOTION' ? send_throttled_message : send_message
    func({'type': name,
          'pos': pos,
          'button': button})
}

function key_event(name, e) {
    send_message({'type': name,
                  'key': e.keyCode})
}

var last_message = new Date

function send_throttled_message(msg) {
    if(new Date - last_message > 100) {
        send_message(msg)
        last_message = new Date
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
