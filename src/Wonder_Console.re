let makeObjInToWindow: unit => unit = [%raw
  param => {|
    window.wonder_console = {};


    window.wonder_console.log = function(msg){
    }

    window.wonder_console.info = function(msg){
    }

    window.wonder_console.debug = function(msg){
    }

    window.wonder_console.error = function(msg){
    }

    window.wonder_console.warn = function(msg){
    }

    window.wonder_console.trace = function(msg){
    }

  |}
];

let log = [%raw
  msg => {|
    if (typeof window === "undefined" || typeof window.wonder_console === "undefined") {
      return;
    }

    window.wonder_console.log(msg);
  |}
];

let info = [%raw
  msg => {|
    if (typeof window === "undefined" || typeof window.wonder_console === "undefined") {
      return;
    }

    window.wonder_console.info(msg);
  |}
];

let debug = [%raw
  msg => {|
    if (typeof window === "undefined" || typeof window.wonder_console === "undefined") {
      return;
    }

    window.wonder_console.debug(msg);
  |}
];

let error = [%raw
  msg => {|
    if (typeof window === "undefined" || typeof window.wonder_console === "undefined") {
      return;
    }

    window.wonder_console.error(msg);
  |}
];

let warn = [%raw
  msg => {|
    if (typeof window === "undefined" || typeof window.wonder_console === "undefined") {
      return;
    }

    window.wonder_console.warn(msg);
  |}
];

let trace = [%raw
  func => {|
    if (typeof window === "undefined" || typeof window.wonder_console === "undefined") {
      return;
    }

    window.wonder_console.trace(func);
  |}
];