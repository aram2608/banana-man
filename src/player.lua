-- Player
function update_player()
    -- gravity
    p.vy += 1
    p.y += p.vy
  
    -- ground check
    if p.y >= 100 then
      p.y = 100
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
  
    -- slide decay
    if p.dash_timer != 0 then
      p.x += p.dash_timer
      p.dash_timer /= 2
      if abs(p.dash_timer) < 0.5 then p.dash_timer = 0 end
    end
  
    -- movement
    if btn(0) then p.x -= p.speed end
    if btn(1) then p.x += p.speed end
  end
  
  function draw_player()
    spr(1, p.x, p.y)
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
      local p = peels[i]
      p.timer -= 1
  
      if abs(p.x - x) < 4 and abs(p.y - y) < 4 then
        vy = -2
        jumps = 1
      end
  
      if p.timer <= 0 then
        del(peels, p)
      end
    end
  end
  
  function draw_peels()
    for p in all(peels) do
      spr(2, p.x, p.y)
    end
  end
  
