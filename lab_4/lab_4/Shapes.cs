using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;
using System.Windows;

namespace lab_4
{
    abstract class Shapes
    {
        protected float velocityX;
        protected float velocityY;
        protected bool upDown;
        protected bool leftRight;
        public bool isCircle { get; set; }
        public abstract Shape Draw();
        public abstract int Motorics(Rect border, Rect shape = new Rect(), bool inputIsCircle = false);
        public abstract Rect getHitBox();
        public abstract void Update();
    }
}
