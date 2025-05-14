#include <QCoreApplication>
#include <QDebug>
#include <QRegularExpression>

void printHelpMessage();
void determineCountingCriteria(QStringList &args,bool &flagA, bool &flagB, bool &flagC, bool &flagD);
QTextStream fileProcessor();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args;
    for (int i = 0; i < argc; ++i) {
        args.append((argv[i]));
    }

    if(args.size() < 2)
    {
       printHelpMessage();
    }



    bool flagA = false, flagB = false, flagC = false, flagD = false;
    determineCountingCriteria(args,flagA, flagB, flagC, flagD);

    QRegularExpression regexA("\b[A-Z][a-zA-Z]{4,}\b");

    int counterA = 0;
    if(flagA)
    {

    }


    return a.exec();
}

QTextStream fileProcessor(int &argumentCounter, QStringList args)
{

}

void determineCountingCriteria(QStringList &args,bool &flagA, bool &flagB, bool &flagC, bool &flagD)
{
    QRegularExpression flagRegex("^-[a-d]+$");
    QRegularExpressionMatch flagMatch;

    for(int i = 1; i < args.size(); ++i)
    {
        flagMatch = flagRegex.match(args[i]);
        if (args[i].startsWith("-") && flagMatch.hasMatch())
        {
            if (args[i].contains("a"))
                flagA = true;
            if (args[i].contains("b"))
                flagB = true;
            if (args[i].contains("c"))
                flagC = true;
            if (args[i].contains("d"))
                flagD = true;
        }
    }

    QTextStream out(stdout);
    out << (flagA ? "Flag A on": "Flag A off") << Qt::endl;
    out << (flagB ? "Flag B on": "Flag B off") << Qt::endl;
    out << (flagC ? "Flag C on": "Flag C off") << Qt::endl;
    out << (flagD ? "Flag D on": "Flag D off") << Qt::endl;
}

void printHelpMessage()
{
    QTextStream out(stdout);
    out << "Usage: count [options] <file1> <file2> ...\n\n";
    out << "This application analyzes text files and, using regular expressions, counts the number of occurrences of the following patterns:\n\n";
    out << "Options:\n";
    out << "  -a    Count words longer than 4 characters that start with a capital letter.\n";
    out << "        (Further capital letters in the word are allowed.)\n";
    out << "  -b    Count hyphenated words.\n";
    out << "        (The hyphen must be inside the word, not at the start or end.)\n";
    out << "  -c    Count words that start and end with the same character.\n";
    out << "  -d    Count words that do not start with a vowel.\n";
    out << "\n";
    out << "If no flags are provided, all the above counts will be performed.\n\n";
    out << "Examples:\n";
    out << "  ./count -a -b file1.txt\n";
    out << "  ./count file1.txt\n";
}
