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
    print("lives: "..lives, 1, 1, 7)
    if dead then print("game over", 40, 64, 8) end
  end
  