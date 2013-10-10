var ws = new WebSocket("ws://" + location.hostname + ":" + location.port + "/ws")
ws.onopen = function() {}
ws.onmessage = function (evt) {
    var received_msg = evt.data
    data = JSON.parse(received_msg)
    var b64 = data.data
    //console.log(data)
    var url = 'data:image/png;base64,' + b64
    var img = new Image()
    img.src = url
    var ctx = $('#screen')[0].getContext('2d')
    img.onload = function() {
        ctx.drawImage(img, 0, 0)
    }
};

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
                  'key': 27})
}

function send_message(msg) {
    console.log(msg)
    ws.send(JSON.stringify(msg))
}

ws.onclose = function()
{
    console.log("Connection is closed...");
};
