-- banana man: basic platformer

-- player table
p = {
    x = 32, y = 64,
    vx = 0, vy = 0,
    w = 8, h = 8,
    on_ground = false,
    speed = 1,
    jumps = 0,
    max_jumps = 2
  }
  
  function _init()
    -- place player at spawn
    p.x = 32
    p.y = 64
  end
  
  function _update()
    -- horizontal movement
    p.vx = 0
    if btn(0) then p.vx = -1 end -- left arrow is button 0
    if btn(1) then p.vx =  1 end -- right arrow is button 1
  
    -- jumping
    if btnp(4) and p.on_ground then -- Z key
      p.vy = -3.5
      p.on_ground = false
    end
  
    -- gravity
    p.vy += 0.2
    if p.vy > 2 then p.vy = 2 end

    -- double jumping
    if btn(0) and p.jumps < p.max_jumps then
      p.jumps += 1 
      end
  
    -- try to move player
    move_player()
  end
  
  function _draw()
    cls()
    map()
    spr(1, p.x, p.y) -- draw player
  end
  
  function move_player()
    -- horizontal movement + collision
    p.x += p.vx
    if is_solid(p.x, p.y) or is_solid(p.x + p.w - 1, p.y) or
       is_solid(p.x, p.y + p.h - 1) or is_solid(p.x + p.w - 1, p.y + p.h - 1) then
      p.x -= p.vx
    end
  
    -- vertical movement + collision
    p.y += p.vy
    if is_solid(p.x, p.y + p.h) or is_solid(p.x + p.w - 1, p.y + p.h) then
      -- hit floor
      p.y = flr((p.y + p.h) / 8) * 8 - p.h
      p.vy = 0
      p.on_ground = true
    elseif is_solid(p.x, p.y) or is_solid(p.x + p.w - 1, p.y) then
      -- hit ceiling
      p.y -= p.vy
      p.vy = 0
    else
      p.on_ground = false
    end
  end
  
  function is_solid(x, y)
    local tile = mget(flr(x / 8), flr(y / 8))
    return fget(tile, 0) -- flag 0 = solid
  end
  