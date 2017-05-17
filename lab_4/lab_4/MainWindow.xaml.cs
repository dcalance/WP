using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace lab_4
{
    public partial class MainWindow : Window
    {
        DispatcherTimer dispatcherTimer = new DispatcherTimer();
        List<Shapes> shapes = new List<Shapes>();
        Rect border = new Rect();
        bool debugHitbox = false;
        public MainWindow()
        {
            InitializeComponent();
            dispatcherTimer.Tick += new EventHandler(animationLoop);
            dispatcherTimer.Interval = TimeSpan.FromMilliseconds(16);
            dispatcherTimer.Start();
            border = new Rect();
            border.Width = animationCanvas.Width;
            border.Height = animationCanvas.Height;
        }
        private void animationLoop(object sender, EventArgs e)
        {
            int res = 0;
            List<Shapes> newShapes = new List<Shapes>();
            while (animationCanvas.Children.Count > 0)
            {
                animationCanvas.Children.RemoveAt(0);
            }
            for (int i = 0; i < shapes.Count; i++)
            {
                Shapes shape = shapes[0];
                shapes.RemoveAt(0);
                if (shapes.Count == 0)
                {
                    res = shape.Motorics(border);
                    switch (res)
                    {
                        case 1:
                            Point center = new Point() { X = shape.getHitBox().X, Y = shape.getHitBox().Y };
                            shape = new Square(center, 40);
                            break;
                    }
                }
                else
                {
                    foreach (var item in shapes)
                    {
                        res = shape.Motorics(border, item.getHitBox(), item.isCircle);
                        if (debugHitbox)
                        {
                            Rect rect = item.getHitBox();
                            Rectangle drawRect = new Rectangle();
                            drawRect.Stroke = Brushes.Red;
                            drawRect.Width = rect.Width;
                            drawRect.Height = rect.Height;
                            Canvas.SetLeft(drawRect, rect.X - rect.Width / 2);
                            Canvas.SetTop(drawRect, rect.Y - rect.Height / 2);
                            animationCanvas.Children.Add(drawRect);
                        }
                        Point center = new Point() { X = shape.getHitBox().X, Y = shape.getHitBox().Y };
                        switch (res)
                        {
                            case 1:
                                shape = new Square(center, 40);
                                break;
                            case 2:
                                if (shapes.Count < 20)
                                {
                                    center = new Point() { X = shape.getHitBox().X - 40, Y = shape.getHitBox().Y };
                                    Point center2 = new Point() { X = 0, Y = 0 };
                                    shape = new Square(center, 20);
                                    Shapes shape2 = new Square(center2, 20);
                                    newShapes.Add(shape2);
                                }
                                break;
                        }
                    }
                }
                shapes.Add(shape);
                shapes.AddRange(newShapes);
                newShapes = new List<Shapes>();
            }
            foreach (var item in shapes)
            {
                item.Update();
                animationCanvas.Children.Add(item.Draw());
            }
        }
        private void animationCanvas_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Circle circle = new Circle(e.GetPosition(animationCanvas), 20);
            Square square = new Square(e.GetPosition(animationCanvas), 30);
            shapes.Add(circle);
            //animationCanvas.Children.Add(circle.Draw());
        }
    }
}
