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
let logVar = log1;

let logJson = (var) => Js.Json.stringify(var |> Obj.magic) |> log1;

let log = (msg) => log1({j|Log: $msg|j});

let info = (msg) => info1({j|Info: $msg|j});

let warn = (msg) => warn1({j|Warn: $msg|j});

let group = group;

let groupCollapsed = groupCollapsed;

let groupEnd = groupEnd;

let _throw = [%bs.raw {|
    function(msg){
            throw new Error(msg)
    }|}];

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

let assert_ = (result: bool, msg) =>
  switch result {
  | false => _throw(msg)
  | true => ()
  };

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

let fatal = (msg) => _throw(msg);

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