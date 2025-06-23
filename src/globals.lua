function init_globals()
    -- player
    x = 40
    y = 100
    vy = 0
    jumps = 0
    max_jumps = 2
    dash_timer = 0
    dash_speed = 4
    speed = 1
  
    -- game state
    lives = 3
    dead = false
  
    -- world
    ants = {}
    peels = {}
  end
  