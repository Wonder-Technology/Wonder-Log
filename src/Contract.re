open Exception;

let _assert = (result: bool, msg) =>
  switch result {
  | false => raise(Check_fail(msg))
  | true => ()
  };

let describe = (message: string, func, ~preCondition=() => true, ()) =>
  preCondition() ?
    try (func()) {
    | Check_fail(failMessage) => throw({j|$message|j})
    } :
    ();

let test = (message: string, func: unit => unit) =>
  try (func()) {
  | Check_fail(failMessage) => throw({j|$message|j})
  };

let testWithMessageFunc = (messageFunc: unit => string, func: unit => unit) =>
  try (func()) {
  | Check_fail(failMessage) =>
    let message = messageFunc();
    throw({j|$message|j})
  };

/* TODO use conditional compilation */
let requireCheck = (f: unit => unit, isTest: bool) : unit =>
  switch isTest {
  | true => f()
  | _ => ()
  };

/* TODO use conditional compilation */
let ensureCheck = (f: 'a => unit, isTest: bool, returnVal: 'a) : 'a =>
  switch isTest {
  | true =>
    f(returnVal);
    returnVal
  | _ => returnVal
  };

let assertFail = () => raise(Check_fail("fail"));

let assertPass = () => ();

let assertTrue = (source: bool) =>
  _assert(source == true, "expect to be true, but actual is false");

let assertFalse = (source: bool) =>
  _assert(source == false, "expect to be false, but actual is true");

let assertJsTrue = (source: Js.boolean) =>
  _assert(source == Js.true_, "expect to be true, but actual is false");

let assertJsFalse = (source: Js.boolean) =>
  _assert(source == Js.false_, "expect to be false, but actual is true");

let assertIsBool = (source: bool) =>
  _assert(source == true || source == false, "expect to be bool, but actual not");

let _isNullableExist = [%bs.raw
  {|
function(source) {
    return source !== undefined && source !== null;
}
|}
];

let assertNullableExist = (source: 'a) =>
  _assert(_isNullableExist(source) |> Js.to_bool, "expect exist, but actual not");

let assertExist = (source: option('a)) =>
  _assert(Js.Option.isSome(source), "expect exist, but actual not");

let assertNotExist = (source: option('a)) =>
  _assert(Js.Option.isNone(source), "expect not exist, but actual exist");

type assertEqual(_) =
  | Int: assertEqual(int)
  | Float: assertEqual(float)
  | String: assertEqual(string);

let _getEqualMessage = (source, target) => {j|"expect to be $target, but actual is $source"|j};

let assertEqual = (type g, kind: assertEqual(g), source: g, target: g) =>
  switch kind {
  | _ => _assert(source == target, _getEqualMessage(source, target))
  };

type assertNotEqual(_) =
  | Int: assertNotEqual(int)
  | Float: assertNotEqual(float)
  | String: assertNotEqual(string);

let _getNotEqualMessage = (source, target) => {j|"expect not to be $target, but actual is $source"|j};

let assertNotEqual = (type g, kind: assertNotEqual(g), source: g, target: g) =>
  switch kind {
  | _ => _assert(source != target, _getNotEqualMessage(source, target))
  };

type assertNumber(_) =
  | Int: assertNumber(int)
  | Float: assertNumber(float);

let assertGt = (type g, kind: assertNumber(g), source: g, target: g) =>
  switch kind {
  | _ => _assert(source > target, {j|expect $source > $target, but actual isn't|j})
  };

let assertGte = (type g, kind: assertNumber(g), source: g, target: g) =>
  switch kind {
  | _ => _assert(source >= target, {j|expect $source >= $target, but actual isn't|j})
  };

let assertLt = (type g, kind: assertNumber(g), source: g, target: g) =>
  switch kind {
  | _ => _assert(source < target, {j|expect $source < $target, but actual isn't|j})
  };

let assertLte = (type g, kind: assertNumber(g), source: g, target: g) =>
  switch kind {
  | _ => _assert(source <= target, {j|expect $source <= $target, but actual isn't|j})
  };

module Operators = {
  let (==) = (a, b) => assertEqual(Int, a, b);
  let (==.) = (a, b) => assertEqual(Float, a, b);
  let (==^) = (a, b) => assertEqual(String, a, b);
  let (<>=) = (a, b) => assertNotEqual(Int, a, b);
  let (<>=.) = (a, b) => assertNotEqual(Float, a, b);
  let (>) = (a, b) => assertGt(Int, a, b);
  let (>.) = (a, b) => assertGt(Float, a, b);
  let (>=) = (a, b) => assertGte(Int, a, b);
  let (>=.) = (a, b) => assertGte(Float, a, b);
  let (<) = (a, b) => assertLt(Int, a, b);
  let (<.) = (a, b) => assertLt(Float, a, b);
  let (<=) = (a, b) => assertLte(Int, a, b);
  let (<=.) = (a, b) => assertLte(Float, a, b);
};