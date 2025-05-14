#include <QCoreApplication>
#include <QDebug>
#include <QRegularExpression>
#include <QFile>
#include <QDir>

void printHelpMessage();
void determineCountingCriteria(QStringList &args,bool &flagA, bool &flagB, bool &flagC, bool &flagD);
QStringList processFileToWords(QFile& file, QTextStream& out);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList args= QCoreApplication::arguments();

    bool flagA = false, flagB = false, flagC = false, flagD = false;

    if(args.size() < 2)
    {
       printHelpMessage();
       flagA = true, flagB = true, flagC = true, flagD = true;
    }

    determineCountingCriteria(args,flagA, flagB, flagC, flagD);


    return a.exec();
}

QStringList processFileToWords(QString& filePath, QTextStream& out)
{
    QStringList lines;
    QStringList words;
    QFile file(filePath);
    QRegularExpression punctuationRegex("[\\\"']");
     // Step 2 check if the file name exists
    if(file.exists()){
        // Step 3 Read the file
        if(!(file.open(QIODevice::ReadOnly | QIODevice::Text)))
        {
            out << "Cannot open file:" << file.errorString();
            return lines;
        }

        QTextStream in(&file);
        QString content = in.readAll();
        qDebug() << content;
        content.replace(punctuationRegex, "");

        words = content.split(QRegularExpression("\\s+"));
        qDebug() << words;

        return words;

    }
    else {
        out << "File does not exist.";
        return lines;
    }

}

void determineCountingCriteria(QStringList &args,bool &flagA, bool &flagB, bool &flagC, bool &flagD)
{
    QRegularExpression flagRegex("^-[a-d]+$");
    QRegularExpressionMatch flagMatch;
    QTextStream out(stdout);
    QStringList lines;

    QRegularExpression regexA("\\b[A-Z][a-zA-Z]{4,}\\b");
    QRegularExpression regexB("\\b[a-z]+-[a-z]+\\b");
    QRegularExpression regexC("\\b([a-z])([a-z\\-]*)\\1\\b", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression regexD("\\b^[^aeiouAEIOU][^\\s]*\\b");


    int wordCountA = 0;
    int wordCountB = 0;
    int wordCountC = 0;
    int wordCountD = 0;

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
        else if (!(args[i].startsWith("-")))
        {
            // Step 1 get the file path
            QString filePath = args[i];
            qDebug() << filePath;
            for(auto word : processFileToWords(filePath,out))
            {
                qDebug() << word;
                if(flagA && regexA.match(word).hasMatch())
                {
                    wordCountA++;
                }
                if(flagB && regexB.match(word).hasMatch())
                {
                    wordCountB++;
                }
                if(flagC && regexC.match(word).hasMatch())
                {
                    qDebug() << "Matches C: " + word;
                    wordCountC++;
                }
                if(flagD && regexD.match(word).hasMatch())
                {
                    qDebug() << "Matches D: " + word;
                    wordCountD++;
                }

            }
            qDebug() << wordCountA;
            qDebug() << wordCountB;
            qDebug() << wordCountC;
            qDebug() << wordCountD;
        }

    }

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
