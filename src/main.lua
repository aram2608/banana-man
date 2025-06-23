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
    draw_peels()
    draw_player()
    camera(p.x - 64, p.y - 64) -- center player on screen
    map(0, 0, 0, 0, 128, 32)   -- draw whole map (or just a slice later)
    print("lives: "..lives, 1, 1, 7)
    if dead then print("game over", 40, 64, 8) end
  end
  