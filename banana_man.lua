-- banana man

-- player table
P = {
    x = 32, y = 64,
    dx = 0, dy = 0,
    w = 8, h = 8,
    on_ground = false
}

function _init()
    --place player at spawn
    P.X = 32
    p.y = 64
end

function _update()
    -- horizontal movement
    p.dx = 0
    if btn(0) then p.dx = -1 end
    if btn(1) then p.dy = 1 end

    --jumping
    if btnp(4) and p.on_ground then
        p.dy = -3.5
        p.on_ground = false
    end

    --gravity
    p.dy += 0.2
    if p.dy > 2 then p.dy = 2 end

    --try to move player
    move_player()
end

function move_player()
    --horizontal movement + collision
    p.x += p.dy
    if is_solid(p.x, p.y) or is_solid(p.x + p.w -1, p.y) or
    is_solid(p.x, p.y + p.h -1) or is_solid(p.x + p.w -1, p.y + p.h -1) then
        p.x -= p.dx
    end

end

function is_solid(x, y)
    local tile = mget(flr(x / 8), flr(y / 8))
    return fget(tile, 0) --flag 0 = solid
end
