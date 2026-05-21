#include <QtTest>

class TestSanity : public QObject
{
    Q_OBJECT

private slots:
    void arithmetic();
    void qstring_basics();
};

void TestSanity::arithmetic()
{
    QCOMPARE(2 + 2, 4);
}

void TestSanity::qstring_basics()
{
    const QString hello = QStringLiteral("hello");
    QCOMPARE(hello.size(), 5);
    QVERIFY(hello.startsWith(QLatin1String("hel")));
}

QTEST_APPLESS_MAIN(TestSanity)
#include "test_sanity.moc"
