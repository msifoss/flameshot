#include "cli/commandargument.h"

#include <QtTest>

class TestCliArgument : public QObject
{
    Q_OBJECT

private slots:
    void default_construction_is_root();
    void named_construction_is_not_root();
    void setters_replace_values();
    void equality_compares_name_and_description();
};

void TestCliArgument::default_construction_is_root()
{
    CommandArgument arg;
    QVERIFY(arg.isRoot());
    QCOMPARE(arg.name(), QString());
    QCOMPARE(arg.description(), QString());
}

void TestCliArgument::named_construction_is_not_root()
{
    CommandArgument arg(QStringLiteral("gui"),
                        QStringLiteral("Start a graphical capture"));
    QVERIFY(!arg.isRoot());
    QCOMPARE(arg.name(), QStringLiteral("gui"));
    QCOMPARE(arg.description(), QStringLiteral("Start a graphical capture"));
}

void TestCliArgument::setters_replace_values()
{
    CommandArgument arg(QStringLiteral("old"), QStringLiteral("old desc"));
    arg.setName(QStringLiteral("new"));
    arg.setDescription(QStringLiteral("new desc"));
    QCOMPARE(arg.name(), QStringLiteral("new"));
    QCOMPARE(arg.description(), QStringLiteral("new desc"));
}

void TestCliArgument::equality_compares_name_and_description()
{
    CommandArgument a(QStringLiteral("gui"), QStringLiteral("desc"));
    CommandArgument b(QStringLiteral("gui"), QStringLiteral("desc"));
    QVERIFY(a == b);

    // Differing description: NOT equal — operator== compares both fields.
    CommandArgument c(QStringLiteral("gui"), QStringLiteral("other"));
    QVERIFY(!(a == c));

    // Differing name: NOT equal.
    CommandArgument d(QStringLiteral("full"), QStringLiteral("desc"));
    QVERIFY(!(a == d));
}

QTEST_APPLESS_MAIN(TestCliArgument)
#include "test_cli_argument.moc"
