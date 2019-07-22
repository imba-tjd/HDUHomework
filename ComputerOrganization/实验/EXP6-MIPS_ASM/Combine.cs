using System.IO;
using System.Linq;

class Combine
{
    static void Main() =>
        File.WriteAllLines("out.txt",
            File.ReadAllLines("1.txt").Zip(
            File.ReadAllLines("2.txt"),
            (a, b) => $"{a} {b}")
        );
}
