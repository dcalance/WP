using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Shapes;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace lab_4
{
    class Square : Shapes
    {
        Rect rect = new Rect();

        public Square(Point inputCenter, float inputSize, float inputVelocityX = 5, float inputVelocityY = 7, bool inputUpDown = false, bool inputLeftRight = false)
        {
            velocityX = inputVelocityX;
            velocityY = inputVelocityY;
            upDown = inputUpDown;
            leftRight = inputLeftRight;
            rect = new Rect();
            rect.X = inputCenter.X;
            rect.Y = inputCenter.Y;
            rect.Width = inputSize;
            rect.Height = inputSize;
            isCircle = false;
        }
        public override int Motorics(Rect border, Rect shape = new Rect(), bool inputIsCircle = false)
        {
            bool borderUpCol = upDown && rect.Top < border.Top;
            bool borderDownCol = !upDown && rect.Bottom > border.Bottom;
            bool borderLeftCol = leftRight && rect.Left < border.Left;
            bool borderRightCol = !leftRight && rect.Right > border.Right;
            int finalVal = 0;

            if (shape.Width != 0 || shape.Height != 0)
            {
                bool checkXAxis =
                    (rect.Right < shape.Right && rect.Right > shape.Left) ||
                    (rect.Left < shape.Right && rect.Left > shape.Left);

                bool checkYAxis =
                    (rect.Bottom > shape.Top && rect.Bottom < shape.Bottom) ||
                    (rect.Top > shape.Top && rect.Top < shape.Bottom);
                bool ballColCheck = checkXAxis && checkYAxis;
                if (upDown && ballColCheck)
                {
                    upDown = false;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
                else
                if (!upDown && ballColCheck)
                {
                    upDown = true;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
                else
                if (leftRight && ballColCheck)
                {
                    leftRight = false;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
                else
                if (!leftRight && ballColCheck)
                {
                    leftRight = true;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
            }
            if (borderDownCol)
            {
                upDown = true;
                velocityX = (velocityX >= 10) ? 10 : velocityX + 1;
                velocityY = (velocityY >= 10) ? 10 : velocityY + 1;
            }
            if (borderUpCol)
            {
                upDown = false;
                velocityX = (velocityX >= 10) ? 10 : velocityX + 1;
                velocityY = (velocityY >= 10) ? 10 : velocityY + 1;
            }
            if (borderLeftCol)
            {
                leftRight = false;
            }
            if (borderRightCol)
            {
                leftRight = true;
            }
            
            return finalVal;
        }
        public override Rect getHitBox()
        {
            return rect;
        }
        public override void Update()
        {
            rect.X = (leftRight) ? rect.X - velocityX : rect.X + velocityX;
            rect.Y = (upDown) ? rect.Y - velocityY : rect.Y + velocityY;
        }
        public override Shape Draw()
        {
            Rectangle drawRect = new Rectangle();
            drawRect.Stroke = Brushes.Black;
            drawRect.Width = rect.Width;
            drawRect.Height = rect.Height;
            Canvas.SetLeft(drawRect, rect.X - rect.Width / 2);
            Canvas.SetTop(drawRect, rect.Y - rect.Height / 2);
            return drawRect;
        }
    }
}
