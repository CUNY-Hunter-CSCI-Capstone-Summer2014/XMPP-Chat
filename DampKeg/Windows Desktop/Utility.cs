using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace DampKeg
{
    class Utility
    {

        public static bool valid_email_address(string incoming)
        {
            Regex rgx = new Regex(".+@.+");
            return rgx.IsMatch(incoming);
        }

    }
}
