open Console;

/* let _isInBrowser = () => {}; */
/* let _isInNodejs = [%bs.raw
     {|
   function(){
   return ((typeof global != "undefined" && global.module) || (typeof module != "undefined")) && typeof module.exports != "undefined";
   }
       |}
   ];

   let _handleDifferentEnv = (handleInNodeJs, handleInOther) =>
     _isInNodejs() ? handleInNodeJs() : handleInOther(); */

let _log = msg => {
  log1(msg);

  Wonder_Console.log(msg);
};

let _info = msg => {
  info1(msg);

  Wonder_Console.info(msg);
};

let _warn = msg => {
  warn1(msg);

  Wonder_Console.warn(msg);
};

let _error = msg => {
  error1(msg);

  Wonder_Console.error(msg);
};

let _trace = func => {
  trace();

  Wonder_Console.trace(func) |> ignore;

  ();
};

let getJsonStr = json => Js.Json.stringify(json |> Obj.magic);

let print = value => {
  _log(value);
  value;
};

let printJson = value => {
  _log(getJsonStr(value));
  value;
};

let logVar = _log;

let logJson = var => Js.Json.stringify(var |> Obj.magic) |> _log;

let log = msg => _log({j|Log: $msg|j});

let info = msg => _info({j|Info: $msg|j});

let warn = msg => _warn({j|Warn: $msg|j});

let group = group;

let groupCollapsed = groupCollapsed;

let groupEnd = groupEnd;

let buildDebugMessage = (~description, ~params, ()) => {j|
  Debug:

  description
  $description

  params
  $params

  |j};

let debugWithFunc = (func, isTest: bool) => isTest ? func() : ();

let rec debug = (buildMessageFunc, isTest: bool) =>
  isTest ?
    {
      _log(buildMessageFunc());
      _trace(debug);
    } :
    ();

let buildDebugJsonMessage = (~description, ~var, ()) => {
  let varStr = Js.Json.stringify(var |> Obj.magic);
  {j|
  DebugJson:

  description
  $description

  variable value
  $varStr
  |j};
};

let rec debugJson = (buildMessageFunc, isTest: bool) =>
  isTest ?
    {
      _log(buildMessageFunc());
      _trace(debugJson);
    } :
    ();

let buildFatalMessage = (~title, ~description, ~reason, ~solution, ~params) => {j|
  Fatal:

  title
  $title

  description
  $description

  reason
  $reason

  solution
  $solution

  params
  $params

   |j};

let fatal = msg => Exception.throw(msg);

let buildErrorMessage = (~title, ~description, ~reason, ~solution, ~params) => {j|
  Error:

  title
  $title

  description
  $description

  reason
  $reason

  solution
  $solution

  params
  $params

   |j};

let rec error = msg => {
  _error(msg);
  _trace(error);
};

let buildAssertMessage = (~expect, ~actual) => {j|expect $expect, but actual $actual|j};