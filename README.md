# simple_code_for_test
only for test some ideas，bug.
mktime(struct tm *tm) function effects my program perfermance。
we don't set argument tm->tm_isdst,so we process 4 millions operations spent over one hour，
so i test different cases perfermance。
