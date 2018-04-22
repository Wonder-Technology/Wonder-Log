type a = {
  a: int,
  b: string
};

open Wonder_jest;

let _ =
  describe(
    "Log",
    () => {
      open Expect;
      open Expect.Operators;
      open Sinon;
      let sandbox = getSandboxDefaultVal();
      beforeEach(() => sandbox := createSandbox());
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      test(
        "test",
        () => {
          /* Log.debug(Log.buildDebugMessage(~title="aaa", ~reason="re", ~solution="so", ~description="de", ~params={j|v1:1, v2:2|j}), true); */
          Log.debug(Log.buildDebugMessage(~description="de", ~params={j|v1:1, v2:2|j}), true);
          let arr = [|1, 2|];
          let obj = {a: 1, b: "bbb"};
          Log.debugJson(Log.buildDebugJsonMessage(~description="de", ~var=obj), true);
         
          Log.error(
            Log.buildErrorMessage(
              ~title="aaa",
              ~reason="re",
              ~solution="so",
              ~description="de",
              ~params={j|v1:1, v2:2|j}
            )
          );
          /* Log.log({j|log v1:$arr|j}); */
          /* Log.logJson(arr); */
          Log.logVar(arr);
          Log.print("print") |> ignore;
          Log.print(obj) |> Log.printJson |> ignore;
          Log.fatal(
            Log.buildFatalMessage(
              ~title="aaa",
              ~reason="re",
              ~solution="so",
              ~description="de",
              ~params={j|v1:1, v2:2|j}
            )
          );
          expect(1) == 1
        }
      )
    }
  );