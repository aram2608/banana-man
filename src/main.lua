function _init()
    init_globals()
  end
  
  function _update()
    if dead then return end
    update_player()
    update_peels()
  end
  
  function _draw()
    cls()
    camera(p.x - 64, p.y - 64) -- center player

    local cel_x = flr(p.x / 8) - 8
    local cel_y = flr(p.y / 8) - 8
    map(cel_x, cel_y, cel_x * 8, cel_y * 8, 16, 16)
    
    print("lives: "..lives, 1, 1, 7)
    draw_peels()
    draw_player()
    if dead then print("game over", 40, 64, 8) end
  end
  