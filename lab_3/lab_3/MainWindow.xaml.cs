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

namespace lab_3
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //object propreties
        bool doFill = false;
        double dThickness = 1;
        SolidColorBrush color;

        //drawing mechanism
        private static string elementPainting;
        Point startingPoint = new Point();
        Point endingPoint = new Point();
        Point curvePoint = new Point();
        bool isDrawing = false;
        bool isDrawingCurve = false;

        public MainWindow()
        {
            InitializeComponent();
            colorPicker.SelectedColor = new Color() { R = 0, G = 0, B = 0, A = 255 };
            elementPainting = "line";

            RoutedCommand newCmd = new RoutedCommand();
            newCmd.InputGestures.Add(new KeyGesture(Key.E, ModifierKeys.Control));
            CommandBindings.Add(new CommandBinding(newCmd, ctrlEPressed));
            newCmd = new RoutedCommand();
            newCmd.InputGestures.Add(new KeyGesture(Key.S, ModifierKeys.Control));
            CommandBindings.Add(new CommandBinding(newCmd, SaveImage));
        }
        private void SaveImage(object sender, RoutedEventArgs e)
        {
            thickness.Text = "CRTL+S";
            
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.FileName = "image"; // Default file name
            dlg.DefaultExt = ".png"; // Default file extension
            dlg.Filter = "Png (.png)|*.png"; // Filter files by extension

            // Show save file dialog box
            Nullable<bool> result = dlg.ShowDialog();

            // Process save file dialog box results
            if (result == true)
            {
                // Save document
                string filename = dlg.FileName;

                RenderTargetBitmap rtb = new RenderTargetBitmap((int)PaintBoard.RenderSize.Width,
                (int)PaintBoard.RenderSize.Height, 96d, 96d, PixelFormats.Default);
                rtb.Render(PaintBoard);
                //var crop = new CroppedBitmap(rtb, new Int32Rect(50, 50, 250, 250));
                BitmapEncoder pngEncoder = new PngBitmapEncoder();
                pngEncoder.Frames.Add(BitmapFrame.Create(rtb));
                using (var fs = System.IO.File.OpenWrite(filename))
                {
                    pngEncoder.Save(fs);
                }
            }
        }
        private void ctrlEPressed(object sender, RoutedEventArgs e)
        {
            ClearAll_Click(sender, e);
        }
        private void Line_Click(object sender, RoutedEventArgs e)
        {
            elementPainting = "line";
        }

        private void Circle_Click(object sender, RoutedEventArgs e)
        {
            elementPainting = "circle";
        }

        private void Curve_Click(object sender, RoutedEventArgs e)
        {
            elementPainting = "curve";
        }

        private void Rect_Click(object sender, RoutedEventArgs e)
        {
            elementPainting = "rect";
        }
        private void Pen_Click(object sender, RoutedEventArgs e)
        {
            elementPainting = "pen";
        }
        private void ClearAll_Click(object sender, RoutedEventArgs e)
        {
            while (PaintBoard.Children.Count > 0)
            {
                PaintBoard.Children.RemoveAt(0);
            }
        }
        private void Eraser_Click(object sender, RoutedEventArgs e)
        {
            colorPicker.SelectedColor = new Color() { R = 255, G = 255, B = 255, A = 255 };
            elementPainting = "pen";
        }
        private void PaintBoard_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (!isDrawing)
            {
                startingPoint = e.GetPosition(PaintBoard);
                isDrawing = !isDrawing;
            }
            else
            {
                endingPoint = e.GetPosition(PaintBoard);
                switch (elementPainting)
                {
                    case "line":
                        Line line = new Line();
                        line.StrokeThickness = dThickness;
                        line.Stroke = color;
                        line.X1 = startingPoint.X;
                        line.Y1 = startingPoint.Y;
                        line.X2 = endingPoint.X;
                        line.Y2 = endingPoint.Y;
                        DrawLine(line);
                        break;
                    case "circle":
                        
                        Ellipse ellipse = new Ellipse();
                        ellipse.Stroke = color;
                        ellipse.StrokeThickness = dThickness;
                        if (doFill)
                        {
                            ellipse.Fill = color;
                        }
                        double diameter = Math.Sqrt(Math.Pow(startingPoint.X - endingPoint.X, 2) + Math.Pow(startingPoint.Y - endingPoint.Y, 2)) * 2;
                        ellipse.Width = diameter;
                        ellipse.Height = diameter;
                        Canvas.SetLeft(ellipse, startingPoint.X - diameter / 2);
                        Canvas.SetTop(ellipse, startingPoint.Y - diameter / 2);
                        PaintBoard.Children.Add(ellipse);
                        break;
                    case "rect":
                        Rectangle rect = new Rectangle();
                        rect.Stroke = color;
                        rect.StrokeThickness = dThickness;
                        if (doFill)
                        {
                            rect.Fill = color;
                        }
                        rect.Width = Math.Abs(startingPoint.X - endingPoint.X);
                        rect.Height = Math.Abs(startingPoint.Y - endingPoint.Y);
                        Canvas.SetLeft(rect, (startingPoint.X > endingPoint.X)? endingPoint.X : startingPoint.X);
                        Canvas.SetTop(rect, (startingPoint.Y > endingPoint.Y) ? endingPoint.Y : startingPoint.Y);
                        PaintBoard.Children.Add(rect);
                        break;
                    case "curve":
                        if (!isDrawingCurve)
                        {
                            isDrawingCurve = true;
                            curvePoint = e.GetPosition(PaintBoard);
                        }
                        else
                        {
                            isDrawingCurve = false;
                            
                            QuadraticBezierSegment segment = new QuadraticBezierSegment();
                            segment.Point1 = curvePoint;
                            segment.Point2 = endingPoint;

                            PathGeometry path = new PathGeometry();
                            PathFigure pathFigure = new PathFigure();
                            pathFigure.StartPoint = startingPoint;
                            path.Figures.Add(pathFigure);

                            pathFigure.Segments.Add(segment);
                            Path p = new Path();
                            p.Stroke = color;
                            p.StrokeThickness = dThickness;
                            p.Data = path;

                            PaintBoard.Children.Add(p);
                        }
                        break;
                }
                isDrawing = (isDrawingCurve) ? true : false;
            }
        }

        private void PaintBoard_MouseMove(object sender, MouseEventArgs e)
        {
            Line line = new Line();
            Point finalPos = new Point();
            line.Stroke = color;
            line.StrokeThickness = dThickness;
            line.X1 = startingPoint.X;
            line.Y1 = startingPoint.Y;
            finalPos = e.GetPosition(PaintBoard);
            line.X2 = finalPos.X;
            line.Y2 = finalPos.Y;

            if (e.LeftButton == MouseButtonState.Pressed)
            {
                if (elementPainting == "pen")
                {
                    DrawLine(line);
                    startingPoint = finalPos;
                }
            }
        }
        private void DrawLine(Line line)
        {
            PaintBoard.Children.Add(line);
        }
        private void HandleCheck(object sender, RoutedEventArgs e)
        {
            doFill = true;
        }
        private void HandleUnchecked(object sender, RoutedEventArgs e)
        {
            doFill = false;
        }

        private void slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            dThickness = e.NewValue + 1;
            thickness.Text = dThickness.ToString();
        }

        private void colorPicker_SelectedColorChanged(object sender, RoutedPropertyChangedEventArgs<Color?> e)
        {
            color = new SolidColorBrush(e.NewValue.Value);
        }

        private void sZoom_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            ScaleTransform scaletransform = new ScaleTransform();
            scaletransform.ScaleX = e.NewValue + 1;
            scaletransform.ScaleY = e.NewValue + 1;
            PaintBoard.LayoutTransform = scaletransform;
        }
    }
}
