void openDisplay(void);
void closeDisplay(void);
void displaySnake(int pieces[][2], int snakeColor);
void displayFood(int x, int y);
void clearDisplay(void);

void openJoystick(void);
void closeJoystick(void);
void checkJoystick(void (*callback)(unsigned int code), int delay);
