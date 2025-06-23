function spawn_ant(x0, y0)
    add(ants, {
      x = x0,
      y = y0,
      dir = 1,
      step = 0,
      max_steps = 20
    })
  end
  
  function update_ants()
    for a in all(ants) do
      a.x += a.dir
      a.step += 1
      if a.step >= a.max_steps then
        a.step = 0
        a.dir *= -1
      end
  
      -- peel collision
      for p in all(peels) do
        if abs(a.x - p.x) < 4 and abs(a.y - p.y) < 4 then
          del(ants, a)
          break
        end
      end
  
      -- player collision
      if abs(a.x - x) < 4 and abs(a.y - y) < 4 then
        lives -= 1
        if lives <= 0 then
          dead = true
        else
          x = 40
          y = 100
          vy = 0
        end
      end
  
      -- despawn offscreen
      if abs(a.x - x) > 64 then
        del(ants, a)
      end
    end
  end
  
  function draw_ants()
    for a in all(ants) do
      spr(3, a.x, a.y)
    end
  end
  