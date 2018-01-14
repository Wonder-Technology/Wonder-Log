open Wonder_jest;

let _ =
  describe(
    "contract",
    () => {
      open Expect;
      open! Expect.Operators;
      open Sinon;
      let sandbox = getSandboxDefaultVal();
      beforeEach(() => sandbox := createSandbox());
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
      describe(
        "requireCheck",
        () => {
          let exec = (isTest) => {
            let stub = createEmptyStub(refJsObjToSandbox(sandbox^));
            Contract.requireCheck(() => stub() |> ignore, isTest) |> ignore;
            stub
          };
          test("if isTest === true, check", () => exec(true) |> expect |> toCalledOnce);
          test("else, not check", () => exec(false) |> expect |> not_ |> toCalledOnce)
        }
      );
      describe(
        "test asserts",
        () =>
          describe(
            "assertNullableExist",
            () =>
              describe(
                "assert Js.Nullable.t('a) should exist",
                () => {
                  test(
                    "Js.Nullable.empty should fail",
                    () =>
                      expect(() => Js.Nullable.empty |> Contract.assertNullableExist)
                      |> toThrowMessage("expect to be exist, but actual not")
                  );
                  test(
                    "not Js.Nullable.empty should pass",
                    () =>
                      expect(() => Js.Nullable.return(1) |> Contract.assertNullableExist)
                      |> not_
                      |> toThrow
                  )
                }
              )
          )
      )
    }
  );