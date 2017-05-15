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
                    shape.Motorics(border);
                }
                else
                {
                    foreach (var item in shapes)
                    {
                        shape.Motorics(border, item.getHitBox());
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
                    }
                }
                shapes.Add(shape);
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
            shapes.Add(square);
            //animationCanvas.Children.Add(circle.Draw());
        }
    }
}
