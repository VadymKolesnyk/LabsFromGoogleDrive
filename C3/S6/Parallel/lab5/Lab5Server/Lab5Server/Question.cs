using System;
using System.Collections.Generic;
using System.Text;

namespace Lab5Server
{
    class Question
    {
        public string QuestionText { get; set; }
        public int CorrectAnswer { get; set; }
        public string[] Answers { get; set; }
    }
}
