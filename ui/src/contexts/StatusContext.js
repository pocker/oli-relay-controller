import React, { createContext, useEffect, useState } from "react";

export const StatusContext = createContext();

export default function StatusContextProvider({ children }) {
  const [status, setStatus] = useState();

  const refresh = () =>
    fetch("/status")
      .then((res) => res.json())
      .then(setStatus);

  useEffect(() => {
    refresh();
    const interval = setInterval(refresh, 5000);
    return () => clearInterval(interval);
  }, []);

  return (
    <StatusContext.Provider value={[status, refresh]}>
      {status && children}
    </StatusContext.Provider>
  );
}
