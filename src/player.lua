-- Player
function update_player()
  -- gravity
  p.vy += 0.5
  p.y += p.vy

  -- vertical collision
  if check_collision(p.x, p.y, p.w, p.h) then
    p.y -= p.vy
    p.vy = 0
    p.jumps = 0
  end

  -- jump
  if btnp(4) and p.jumps < p.max_jumps then
    p.vy = -5
    p.jumps += 1
  end

  -- peel slide
  if btnp(5) and p.dash_timer == 0 then
    if btn(0) then p.dash_timer = -p.dash_speed end
    if btn(1) then p.dash_timer = p.dash_speed end
    spawn_peel(p.x, p.y)
  end

  -- peel decay slide
  if p.dash_timer != 0 then
    p.x += p.dash_timer
    p.dash_timer /= 2
    if abs(p.dash_timer) < 0.5 then p.dash_timer = 0 end
  end

  -- horizontal collision & input
  move_player()
end

function check_collision(x, y, w, h)
  return is_solid(x, y) or
        is_solid(x + w - 1, y) or
        is_solid(x, y + h - 1) or
        is_solid(x + w - 1, y + h - 1)
end

  
  function draw_player()
    spr(0, p.x, p.y)
  end

  function move_player()
    -- reset movement
    p.dx = 0
  
    -- input
    if btn(0) then p.dx = -1 end -- left
    if btn(1) then p.dx = 1 end  -- right
  
    -- apply movement
    p.x += p.dx
  
    -- collision check (4 corners)
    if is_solid(p.x, p.y) or
      is_solid(p.x + p.w - 1, p.y) or
      is_solid(p.x, p.y + p.h - 1) or
      is_solid(p.x + p.w - 1, p.y + p.h - 1) then
      -- undo move
      p.x -= p.dx
    end
  end
  
  function is_solid(x, y)
    local tile = mget(flr(x / 8), flr(y / 8))
    return fget(tile, 0) -- tile is solid if flag 0 is set
  end

-- Banana Peels
  function spawn_peel(px, py)
    add(peels, {
      x = px,
      y = py,
      timer = 120
    })
  end
  
  function update_peels()
    for i=#peels,1,-1 do
      local pe = peels[i]
      pe.timer -= 1
  
      -- slip check
      if abs(pe.x - p.x) < 4 and abs(pe.y - p.y) < 4 and pe.timer > 0 then
        p.vy = -2
        p.jumps = 1
      end
  
      if pe.timer <= 0 then
        del(peels, pe)
      end
    end
  end
  
  
  function draw_peels()
    for peel in all(peels) do
      spr(3, peel.x, peel.y)
    end
  end
