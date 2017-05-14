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
            if (!upDown && rect.Bottom > border.Bottom || !upDown && rect.Bottom > shape.Bottom)
            {
                upDown = true;
            }
            if (upDown && rect.Top < border.Top || upDown && rect.Top < shape.Top)
            {
                upDown = false;
            }
            if (leftRight && rect.Left < border.Left || leftRight && rect.Left < shape.Left)
            {
                leftRight = false;
            }
            if (!leftRight && rect.Right > border.Right || !leftRight && rect.Right > shape.Right)
            {
                leftRight = true;
            }
            rect.X = (leftRight) ? rect.X - velocityX : rect.X + velocityX;
            rect.Y = (upDown) ? rect.Y - velocityY : rect.Y + velocityY;
        }
        public override Rect getHitBox()
        {
            return rect;
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
