
using SharpGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Function
    {

        public Func<double, double, double> targetFunction;
        public Func<double, double, double> TargetFunction
        {
            get { return targetFunction; }
            set 
            {
                if (value != null)
                {
                    targetFunction = value;
                }
            }
        }
        public bool DrawAntigradients { get; set; } = false;
        public void Draw(OpenGL gl)
        {

        }




    }
}
