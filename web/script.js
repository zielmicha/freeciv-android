
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
var animation_timer_id

function handle_screen(image, frame) {
    if(animation_progress == null && frame.allow_animation != 0) {
        if(last_screen_content != null && frame.id != last_screen_id) {
            start_animation(image, frame.allow_animation)
        }
    }
    last_screen_id = frame.id
    last_screen_content = image
    draw_screen()
}

function draw_screen() {
    canvas_ctx.fillStyle = '#500'
    canvas_ctx.fill()
    if(animation_progress == null) {
        canvas_ctx.drawImage(last_screen_content, 0, 0)
    } else {
        var w = $('canvas')[0].width
        console.log("anim", typeof animation_source, typeof animation_target)
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
        draw_screen()
    } else {
        clearInterval(animation_timer_id)
    }
}

ws.onmessage = function (evt) {
    var received_msg = evt.data
    data = JSON.parse(received_msg)
    var b64 = data.data
    var url = 'data:image/png;base64,' + b64
    var img = new Image()
    img.src = url
    canvas_ctx = $('#screen')[0].getContext('2d')
    img.onload = function() {
        handle_screen(img, data)
    }
};

// events

var is_down = false

$(function() {
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
    var button = e.button
    if(button == 2) button = 1
    send_message({'type': name,
                  'pos': pos,
                  'button': button})
}

function key_event(name, e) {
    send_message({'type': name,
                  'key': e.keyCode})
}

function send_message(msg) {
    console.log(msg)
    ws.send(JSON.stringify(msg))
}

ws.onclose = function()
{
    console.log("Connection is closed...");
};
