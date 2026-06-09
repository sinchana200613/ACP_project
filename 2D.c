#include <stdio.h>
#include <stdlib.h>

#define ROWS 30
#define COLS 60
#define MAX_SHAPES 100

char canvas[ROWS][COLS];

typedef struct
{
    int type;       // 1-Rectangle 2-Line 3-Triangle 4-Circle
    int x1, y1;
    int x2, y2;
    int width, height;
    int radius;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void initCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i,j;

    printf("\n");

    for(i=0;i<ROWS;i++)
    {
        for(j=0;j<COLS;j++)
        {
            putchar(canvas[i][j]);
            putchar(' ');
        }
        printf("\n");
    }
}
void drawRectangle(int x, int y, int width, int height)
{
    int i, j;

    for(i = y; i < y + height && i < ROWS; i++)
    {
        for(j = x; j < x + width && j < COLS; j++)
        {
            if(i >= 0 && j >= 0)
                canvas[i][j] = '*';
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int i;

    if(y1 == y2)
    {
        if(x1 > x2)
        {
            int temp = x1;
            x1 = x2;
            x2 = temp;
        }

        for(i = x1; i <= x2 && i < COLS; i++)
        {
            if(i >= 0 && y1 >= 0 && y1 < ROWS)
                canvas[y1][i] = '*';
        }
    }
    else if(x1 == x2)
    {
        if(y1 > y2)
        {
            int temp = y1;
            y1 = y2;
            y2 = temp;
        }

        for(i = y1; i <= y2 && i < ROWS; i++)
        {
            if(i >= 0 && x1 >= 0 && x1 < COLS)
                canvas[i][x1] = '*';
        }
    }
}

void drawTriangle(int x, int y, int height)
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j <= i; j++)
        {
            if(y + i < ROWS && x + j < COLS)
                canvas[y + i][x + j] = '*';
        }
    }
}

void drawCircle(int cx, int cy, int radius)
{
    int x, y;

    for(y = 0; y < ROWS; y++)
    {
        for(x = 0; x < COLS; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            if(dx * dx + dy * dy <= radius * radius)
            {
                canvas[y][x] = '*';
            }
        }
    }
}

void redrawCanvas()
{
    int i;

    initCanvas();

    for(i = 0; i < shapeCount; i++)
    {
        switch(shapes[i].type)
        {
            case 1:
                drawRectangle(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].width,
                    shapes[i].height
                );
                displayCanvas();
                break;

            case 2:
                drawLine(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].x2,
                    shapes[i].y2
                );
                displayCanvas();
                break;

            case 3:
                drawTriangle(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].height
                );
                displayCanvas();
                break;

            case 4:
                drawCircle(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].radius
                );
                displayCanvas();
                break;
        }
    }
}

void addRectangle()
{
    Shape s;

    s.type = 1;

    printf("Enter x y width height: ");
    scanf("%d%d%d%d",
          &s.x1,
          &s.y1,
          &s.width,
          &s.height);

    shapes[shapeCount++] = s;
    redrawCanvas();
}

void addLine()
{
    Shape s;

    s.type = 2;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d%d%d%d",
          &s.x1,
          &s.y1,
          &s.x2,
          &s.y2);

    shapes[shapeCount++] = s;
    redrawCanvas();
}

void addTriangle()
{
    Shape s;

    s.type = 3;

    printf("Enter x y height: ");
    scanf("%d%d%d",
          &s.x1,
          &s.y1,
          &s.height);

    shapes[shapeCount++] = s;
    redrawCanvas();
}

void addCircle()
{
    Shape s;

    s.type = 4;

    printf("Enter centerX centerY radius: ");
    scanf("%d%d%d",
          &s.x1,
          &s.y1,
          &s.radius);

    shapes[shapeCount++] = s;
    redrawCanvas();
}

void deleteShape()
{
    int index, i;

    printf("Enter shape number to delete (0-%d): ",
           shapeCount - 1);
    scanf("%d", &index);

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid shape number\n");
        return;
    }

    for(i = index; i < shapeCount - 1; i++)
    {
        shapes[i] = shapes[i + 1];
    }

    shapeCount--;

    redrawCanvas();
}

void modifyShape()
{
    int index;

    printf("Enter shape number to modify (0-%d): ",
           shapeCount - 1);
    scanf("%d", &index);

    if(index < 0 || index >= shapeCount)
    {
        printf("Invalid shape number\n");
        return;
    }

    switch(shapes[index].type)
    {
        case 1:
            printf("Enter new x y width height: ");
            scanf("%d%d%d%d",
                  &shapes[index].x1,
                  &shapes[index].y1,
                  &shapes[index].width,
                  &shapes[index].height);
            break;

        case 2:
            printf("Enter new x1 y1 x2 y2: ");
            scanf("%d%d%d%d",
                  &shapes[index].x1,
                  &shapes[index].y1,
                  &shapes[index].x2,
                  &shapes[index].y2);
            break;

        case 3:
            printf("Enter new x y height: ");
            scanf("%d%d%d",
                  &shapes[index].x1,
                  &shapes[index].y1,
                  &shapes[index].height);
            break;

        case 4:
            printf("Enter new centerX centerY radius: ");
            scanf("%d%d%d",
                  &shapes[index].x1,
                  &shapes[index].y1,
                  &shapes[index].radius);
            break;
    }

    redrawCanvas();
}

void listShapes()
{
    int i;

    printf("\nStored Shapes:\n");

    for(i = 0; i < shapeCount; i++)
    {
        printf("%d -> ", i);

        switch(shapes[i].type)
        {
            case 1:
                printf("Rectangle\n");
                break;

            case 2:
                printf("Line\n");
                break;

            case 3:
                printf("Triangle\n");
                break;

            case 4:
                printf("Circle\n");
                break;
        }
    }
}

int main()
{
    int choice;

    initCanvas();

    do
    {
        printf("\n\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Shape\n");
        printf("6. Modify Shape\n");
        printf("7. Display Picture\n");
        printf("8. List Shapes\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addRectangle();
                break;

            case 2:
                addLine();
                break;

            case 3:
                addTriangle();
                break;

            case 4:
                addCircle();
                break;

            case 5:
                deleteShape();
                break;

            case 6:
                modifyShape();
                break;

            case 7:
                displayCanvas();
                break;

            case 8:
                listShapes();
                break;

            case 0:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    } while(choice != 0);

    return 0;
}