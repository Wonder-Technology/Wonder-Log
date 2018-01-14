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
let getJsonStr = (json) => Js.Json.stringify(json |> Obj.magic);

let print = (value) => {
  log1(value);
  value
};

let printJson = (value) => {
  log1(getJsonStr(value));
  value
};

let logVar = log1;

let logJson = (var) => Js.Json.stringify(var |> Obj.magic) |> log1;

let log = (msg) => log1({j|Log: $msg|j});

let info = (msg) => info1({j|Info: $msg|j});

let warn = (msg) => warn1({j|Warn: $msg|j});

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

let debug = (buildMessageFunc, isTest: bool) =>
  isTest ?
    {
      log1(buildMessageFunc());
      trace()
      /* log1({j|
         DebugEnd
               |j}) */
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
  |j}
};

let debugJson = (buildMessageFunc, isTest: bool) =>
  isTest ?
    {
      log1(buildMessageFunc());
      trace()
      /* log1({j|
         DebugJsonEnd
               |j}) */
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

let fatal = (msg) => Exception.throw(msg);

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

let error = (msg) => {
  error1(msg);
  trace()
  /* log1({j|
     ErrorEnd
           |j}) */
};

let buildAssertMessage = (~expect, ~actual) => {j|expect $expect, but actual $actual|j};