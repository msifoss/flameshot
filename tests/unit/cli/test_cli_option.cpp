#include "cli/commandoption.h"

#include <QtTest>

class TestCliOption : public QObject
{
    Q_OBJECT

private slots:
    void single_name_constructor_stores_one_name();
    void multi_name_constructor_preserves_order();
    void dashed_names_single_char_gets_one_dash();
    void dashed_names_multi_char_gets_two_dashes();
    void dashed_names_mixed_aliases();
    void default_checker_accepts_anything();
    void custom_checker_runs_and_sets_error_msg();
    void set_value_auto_fills_value_name_when_blank();
    void equality_compares_names_description_and_value_name();
};

void TestCliOption::single_name_constructor_stores_one_name()
{
    CommandOption opt(QStringLiteral("p"), QStringLiteral("path"));
    QCOMPARE(opt.names().size(), 1);
    QCOMPARE(opt.names().first(), QStringLiteral("p"));
    QCOMPARE(opt.description(), QStringLiteral("path"));
}

void TestCliOption::multi_name_constructor_preserves_order()
{
    QStringList names{ QStringLiteral("h"), QStringLiteral("help") };
    CommandOption opt(names, QStringLiteral("show help"));
    QCOMPARE(opt.names(), names);
}

void TestCliOption::dashed_names_single_char_gets_one_dash()
{
    CommandOption opt(QStringLiteral("v"), QStringLiteral("version"));
    QCOMPARE(opt.dashedNames(), QStringList{ QStringLiteral("-v") });
}

void TestCliOption::dashed_names_multi_char_gets_two_dashes()
{
    CommandOption opt(QStringLiteral("version"), QStringLiteral("version"));
    QCOMPARE(opt.dashedNames(), QStringList{ QStringLiteral("--version") });
}

void TestCliOption::dashed_names_mixed_aliases()
{
    CommandOption opt(
      QStringList{ QStringLiteral("v"), QStringLiteral("version") },
      QStringLiteral("version"));
    const QStringList expected{ QStringLiteral("-v"),
                                QStringLiteral("--version") };
    QCOMPARE(opt.dashedNames(), expected);
}

void TestCliOption::default_checker_accepts_anything()
{
    CommandOption opt(QStringLiteral("p"), QStringLiteral("path"));
    QVERIFY(opt.checkValue(QStringLiteral("anything")));
    QVERIFY(opt.checkValue(QString()));
    QVERIFY(opt.checkValue(QStringLiteral("/with/slashes")));
}

void TestCliOption::custom_checker_runs_and_sets_error_msg()
{
    CommandOption opt(QStringLiteral("d"), QStringLiteral("delay"));
    opt.addChecker(
      [](const QString& v) {
          bool ok = false;
          v.toInt(&ok);
          return ok;
      },
      QStringLiteral("delay must be an integer"));

    QVERIFY(opt.checkValue(QStringLiteral("123")));
    QVERIFY(!opt.checkValue(QStringLiteral("not a number")));
    QCOMPARE(opt.errorMsg(), QStringLiteral("delay must be an integer"));
}

void TestCliOption::set_value_auto_fills_value_name_when_blank()
{
    // Quirky behavior of CommandOption::setValue(): if valueName is empty
    // when setValue runs, it gets auto-populated with the literal "value".
    // Locking this in so it's not silently changed.
    CommandOption opt(QStringLiteral("p"), QStringLiteral("path"));
    QVERIFY(opt.valueName().isEmpty());
    opt.setValue(QStringLiteral("/tmp/x"));
    QCOMPARE(opt.value(), QStringLiteral("/tmp/x"));
    QCOMPARE(opt.valueName(), QStringLiteral("value"));

    // If valueName is already set, setValue leaves it alone.
    CommandOption opt2(QStringLiteral("p"),
                       QStringLiteral("path"),
                       QStringLiteral("PATH"));
    opt2.setValue(QStringLiteral("/tmp/y"));
    QCOMPARE(opt2.valueName(), QStringLiteral("PATH"));
}

void TestCliOption::equality_compares_names_description_and_value_name()
{
    CommandOption a(
      QStringLiteral("p"), QStringLiteral("path"), QStringLiteral("PATH"));
    CommandOption b(
      QStringLiteral("p"), QStringLiteral("path"), QStringLiteral("PATH"));
    QVERIFY(a == b);

    // Different valueName breaks equality.
    CommandOption c(
      QStringLiteral("p"), QStringLiteral("path"), QStringLiteral("OTHER"));
    QVERIFY(!(a == c));

    // Equality ignores the runtime-mutable `value` field (no setValue
    // mutation on `a` to test against; documenting the negative-space
    // behavior so a future change to operator== is a deliberate decision
    // rather than an accident).
    a.setValue(QStringLiteral("/tmp"));
    QVERIFY(a == b);
}

QTEST_APPLESS_MAIN(TestCliOption)
#include "test_cli_option.moc"
