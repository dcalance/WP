using System;
using System.Windows;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Shapes;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace lab_4
{
    class Circle : Shapes
    {
        public Point center = new Point();
        float radius;

        public Circle(Point inputCenter, float inputRadius, float inputVelocityX = 5, float inputVelocityY = 5, bool inputUpDown = false, bool inputLeftRight = false)
        {
            center = inputCenter;
            radius = inputRadius;
            velocityX = inputVelocityX;
            velocityY = inputVelocityY;
            upDown = inputUpDown;
            leftRight = inputLeftRight;
            isCircle = true;
        }
        public override void Update()
        {
            center.X = (leftRight) ? center.X - velocityX : center.X + velocityX;
            center.Y = (upDown) ? center.Y - velocityY : center.Y + velocityY;
        }
        public override int Motorics(Rect border, Rect shape = new Rect(), bool inputIsCircle = false)
        {
            int finalVal = 0;
            bool borderDownCol = !upDown && center.Y + radius > border.Bottom;
            bool borderUpCol = upDown && center.Y - radius < border.Top;
            bool borderLeftCol = leftRight && center.X - radius < border.Left;
            bool borderRightCol = !leftRight && center.X + radius > border.Right;

            if (shape.Width != 0 || shape.Height != 0)
            {
                bool checkXAxis =
                    (center.X + radius < shape.Right && center.X + radius > shape.Left) ||
                    (center.X - radius < shape.Right && center.Y - radius > shape.Left);

                bool checkYAxis =
                    (center.Y + radius > shape.Top && center.Y + radius < shape.Bottom) ||
                    (center.Y - radius > shape.Top && center.Y - radius < shape.Bottom);
                bool ballColCheck = checkXAxis && checkYAxis;
                if (!upDown && ballColCheck)
                {
                    upDown = true;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
                if (upDown && ballColCheck)
                {
                    upDown = false;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
                if (leftRight && ballColCheck)
                {
                    leftRight = false;
                    if (isCircle == inputIsCircle)
                    {
                        finalVal = 2;
                    }
                }
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
                finalVal = 1;
            }
            if (borderRightCol)
            {
                leftRight = true;
                finalVal = 1;
            }
            return finalVal;
        }
        public override Rect getHitBox()
        {
            Rect hitBox = new Rect();
            hitBox.X = center.X;
            hitBox.Y = center.Y;
            hitBox.Width = radius * 2;
            hitBox.Height = radius * 2;

            return hitBox;
        }
        public override Shape Draw()
        {
            Ellipse ellipse = new Ellipse();
            ellipse.Stroke = Brushes.Black;
            double diameter = radius * 2;
            ellipse.Width = diameter;
            ellipse.Height = diameter;
            Canvas.SetLeft(ellipse, center.X - diameter / 2);
            Canvas.SetTop(ellipse, center.Y - diameter / 2);
            return ellipse;
        }

    }
}
