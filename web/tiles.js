var tiles_draw_at
var map_pos = [0, 0]
var tile_size = 64
var tile_storage = {}

function tiles_process_message(m) {
    //console.log(m)
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

function tiles_draw() {
    var pos = tiles_draw_at
    if(!pos) return;
    canvas_ctx.clearRect(pos[0], pos[1], pos[2], pos[3])
    var w = pos[2]
    var h = pos[3]

    for(var x=0; x < w + tile_size; x+=tile_size) {
        for(var y=0; y < h + tile_size; y+=tile_size) {
            tile_draw(pos, x, y)
        }
    }
}

function tile_draw(pos, x, y) {
    var key = x + ',' + y
    var tile = tile_storage[key]
    if(tile) {
        canvas_ctx.drawImage(tile_storage[key], pos[0] + x, pos[1] + y)
    }
}

function tile_round(v) {
    return parseInt(v / tile_size) * tile_size
}
