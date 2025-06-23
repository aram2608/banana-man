-- Player
function update_player()
    -- gravity
    vy += 1
    y += vy
  
    -- ground check
    if y >= 100 then
      y = 100
      vy = 0
      jumps = 0
    end
  
    -- jump
    if btnp(4) and jumps < max_jumps then
      vy = -5
      jumps += 1
    end
  
    -- peel slide
    if btnp(5) and dash_timer == 0 then
      if btn(0) then dash_timer = -dash_speed end
      if btn(1) then dash_timer = dash_speed end
      spawn_peel(x, y)
    end
  
    -- slide decay
    if dash_timer != 0 then
      x += dash_timer
      dash_timer /= 2
      if abs(dash_timer) < 0.5 then dash_timer = 0 end
    end
  
    -- movement
    if btn(0) then x -= speed end
    if btn(1) then x += speed end
  end
  
  function draw_player()
    spr(1, x, y)
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
  