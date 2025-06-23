function _init()
    init_globals()
    spawn_ant(20, 100)
    spawn_ant(80, 100)
  end
  
  function _update()
    if dead then return end
    update_player()
    update_ants()
    update_peels()
  end
  
  function _draw()
    cls()
    draw_peels()
    draw_ants()
    draw_player()
    print("lives: "..lives, 1, 1, 7)
    if dead then print("game over", 40, 64, 8) end
  end
  