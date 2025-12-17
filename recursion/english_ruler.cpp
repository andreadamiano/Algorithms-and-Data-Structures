#include <iostream>

//draw a tick of the ruler
void drawOneTick(int tickLenght, int tickLabel =-1)
{
    for (int i =0; i<tickLenght; i++)
        std::cout <<"-";  //draw a tick 
    if (tickLabel>=0) 
        std::cout << " " << tickLabel; //draw the label (for the bigger ticks)
    
    std::cout << std::endl; 
}   


void drawTicks (int tickLenght)
{
    if(tickLenght > 0) //base case, recursion stop when it reaches 0 
    {
        drawTicks(tickLenght-1); //recursively draw left ticks (An interval with a central tick length L−1)
        drawOneTick(tickLenght); //draw center tick (of lenght L)
        drawTicks(tickLenght-1); //recursively draw right ticks (An interval with a central tick length L−1)
    }
}


void drawRuler(int inches, int majorLenght)
{
    drawOneTick(majorLenght, 0); //draw first tick 
    for (int i =1; i<=inches; i++)
    {
        drawTicks(majorLenght-1); 
        drawOneTick(majorLenght, i); //draw i-th big tick 
    }
}

int main ()
{
    drawRuler(1, 5); 
}