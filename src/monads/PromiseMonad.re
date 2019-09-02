open Utils;

module type T = {
    include Monad.T;

    let throw: exn => t('a);
    let catch: (t('a), Js.Promise.error => t('a)) => t('a);
    let make: Js.Promise.t('a) => t('a);
    let extract: t('a) => Js.Promise.t('a);
};

module Make: T = {
    type t('a) = Js.Promise.t('a);

    let bind = (x, f) => Js.Promise.then_(f, x);
    let return = Js.Promise.resolve;
    let throw = x => Js.Promise.reject(raise(x));
    let catch = (x, f) => Js.Promise.catch(f, x);
    let make = id;
    let extract = id;
};

module Ex = {
    include Monad.Ex(Make);

    let (>>|) = Make.catch;
};