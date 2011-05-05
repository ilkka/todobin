// Implementation of QML private storage of JS objects
// pilfered from http://wiki.forum.nokia.com/index.php/Store_JavaScript_object_references_in_QML_objects

.pragma library // It's a lib so all data is shared

var _privs = {}

function priv(key) {
    var h = key.toString() // the "hash": okay since there's a pointer in there
    var o = _privs[key]
    if (!o) {
        o = {}
        _privs[key] = o
    }
    return o
}
