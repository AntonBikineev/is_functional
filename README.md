is_functional
=============

-------------------------------------------
type traits for types with operator()
-------------------------------------------

These traits are created for compile-time check of types
with overloaded operator(). It works for usual operator(),
templated operator(), for invisibly generated closure type
of lambdas.
Usage is similar with the other boost type traits:
is_functional<T>::value
