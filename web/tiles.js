var tiles_draw_at
var map_pos = [0, 0]
var tile_size = 128
var tile_storage = {}
var tiles_init_done = false
var tiles_draw_frame = false

function tiles_process_message(m) {
    if(m.draw_at) {
        tiles_draw_at = m.draw_at
    }
    if(m.data) {
        load_image_from_b64(m.data, function(img) {
            console.log("loaded", m.id)
            tile_storage[m.id] = img
        })
    }
}

function tiles_init() {
    send_message({'type': 'tile_init'})
}

function tiles_draw() {
    if(!tiles_init_done) {
        // todo: reinit for each game
        tiles_init_done = true
        tiles_init()
    }
    var pos = [tiles_draw_at[0], tiles_draw_at[1],
               tiles_draw_at[2], tiles_draw_at[3]]
    canvas_ctx.fillStyle = 'black'
    canvas_ctx.fillRect(pos[0], pos[1], pos[2], pos[3])
    if(drag_offsets.map) {
        pos[0] += drag_offsets.map[0]
        pos[1] += drag_offsets.map[1]
    }
    var w = pos[2]
    var h = pos[3]
    // notify about center
    tiles_notify_about_position(pos[0] - w / 2, pos[1] - h / 2)
    var x_start = nround(-pos[0], tile_size)
    var y_start = nround(-pos[1], tile_size)

    for(var x=-tile_size; x < w + tile_size*2; x+=tile_size) {
        for(var y=-tile_size; y < h + tile_size*2; y+=tile_size) {
            tile_draw(pos, x_start + x, y_start + y)
        }
    }
}

function nround(i, r) {
    return parseInt(i / r) * r
}

var tiles_notified_about = null

function tiles_notify_about_position(x, y) {
    key = x + ',' + y
    if(key != tiles_notified_about) {
        tiles_notified_about = key
        send_throttled_message({'type': 'tile_posnotify',
                                'pos': [x, y]})
    }
}

function tile_draw(pos, x, y) {
    var key = x + ',' + y
    var tile = tile_storage[key]
    if(tile) {
        draw_image_cropped(tile_storage[key], pos[0] + x, pos[1] + y,
                           layerlist.map.pos[0], layerlist.map.pos[1],
                           layerlist.map.size[0], layerlist.map.size[1])
    }
    if(tiles_draw_frame) {
        canvas_ctx.beginPath();
        canvas_ctx.rect(pos[0] + x, pos[1] + y, tile_size - 4, tile_size - 4);
        canvas_ctx.lineWidth = 1;
        canvas_ctx.strokeStyle = 'yellow';
        canvas_ctx.stroke();
    }
}

function tile_round(v) {
    return parseInt(v / tile_size) * tile_size
}

function tiles_center_at(pos) {
    console.log("center at" + pos)
    drag_offsets.map = [-pos[0] + layerlist.map.size[0] / 2,
                        -pos[1] + layerlist.map.size[1] / 2]
}

function draw_image_cropped(img, x, y, cx, cy, cw, ch) {
    // crops image from left to rect (cx, cy, cw, ch)
    // real cropping also may be useful, but not used anywhere
    var sw = img.width
    var sh = img.height
    var ssx = 0, ssy = 0
    if(x < cx) {
        sw -= (cx - x)
        ssx += (cx - x)
        x = cx
    }
    if(sw <= 0) return
    canvas_ctx.drawImage(img, ssx, ssy, sw, sh, x, y, sw, sh)
}
