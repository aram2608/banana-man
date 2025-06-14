FUNCTION _INIT() -- Runs once at beginning
  -- ALWAYS START ON WHITE
  COL = 7
END
 
FUNCTION _UPDATE() -- run once every 30 fps
  -- PRESS X FOR A RANDOM COLOUR
  IF (BTNP(5)) COL = 8 + RND(8)
END
 
FUNCTION _DRAW() -- run every frame
  CLS(1)
  CIRCFILL(64,64,32,COL)
END