function init_globals()
    -- player
    p = {
    x = 40,
    y = 100,
    vy = 0,
    vx=0,
    jumps = 0,
    max_jumps = 2,
    dash_timer = 0,
    dash_speed = 4,
    speed = 3,
    w = 8,
    h = 8,
    onground=false,
    coyote_timer=0,
    }
  
    -- game state
    lives = 3
    dead = false
  
    -- world
    ants = {}
    peels = {}
  end
  