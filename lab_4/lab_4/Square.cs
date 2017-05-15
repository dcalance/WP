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
        }
        public override void Motorics(Rect border, Rect shape = new Rect())
        {
            bool borderUpCol = upDown && rect.Top < border.Top;
            bool borderDownCol = !upDown && rect.Bottom > border.Bottom;
            bool borderLeftCol = leftRight && rect.Left < border.Left;
            bool borderRightCol = !leftRight && rect.Right > border.Right;

            if (shape.Width == 0 || shape.Height == 0)
            {
                if (borderDownCol)
                {
                    upDown = true;
                }
                if (borderUpCol)
                {
                    upDown = false;
                }
                if (borderLeftCol)
                {
                    leftRight = false;
                }
                if (borderRightCol)
                {
                    leftRight = true;
                }
            }
            else
            {
                bool checkXAxis =
                    (rect.Right < shape.Right && rect.Right > shape.Left) ||
                    (rect.Left < shape.Right && rect.Left > shape.Left);

                bool checkYAxis =
                    (rect.Bottom > shape.Top && rect.Bottom < shape.Bottom) ||
                    (rect.Top > shape.Top && rect.Top < shape.Bottom);
                bool ballColCheck = checkXAxis && checkYAxis;
                if (borderDownCol || !upDown && ballColCheck)
                {
                    upDown = true;
                }
                else
                if (borderUpCol || upDown && ballColCheck)
                {
                    upDown = false;
                }
                else
                if (borderLeftCol || leftRight && ballColCheck)
                {
                    leftRight = false;
                }
                else
                if (borderRightCol || !leftRight && ballColCheck)
                {
                    leftRight = true;
                }
            }
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
