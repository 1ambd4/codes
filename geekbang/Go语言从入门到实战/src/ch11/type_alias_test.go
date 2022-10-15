package type_alias_test

import "testing"

type INT int

func TestTypeAlias(t *testing.T) {
    var a INT = 233
    t.Log(a)
}
