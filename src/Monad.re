module type MonadType = {
    type t('a);

    let return: 'a => t('a);

    let (>>=): (t('a), 'a => t('b)) => t('b);
};

module type PromiseMonadType = {
    include MonadType;

    let throw: exn => t('a);
    
    let (>>|): (t('a), Js.Promise.error => t('a)) => t('a);
};

module PromiseMonad: PromiseMonadType = {
    type t('a) = Js.Promise.t('a);

    let return = Js.Promise.resolve;
    let throw = x => Js.Promise.reject(raise(x));

    let (>>=) = (x, f) => Js.Promise.then_(f, x);
    let (>>|) = (x, f) => Js.Promise.catch(f, x);
};
