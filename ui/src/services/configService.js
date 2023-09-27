export function setUser(username, password) {
  return fetch("/config", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ user: { username, password } }),
  });
}

export function setWifi(ssid, password) {
  return fetch("/config", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ wifi: { ssid, password } }),
  });
}

export function setConfig(config) {
  return fetch("/config", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({
      profile: {
        configuration: config,
      },
    }),
  });
}

export function setActiveProfile(profile) {
  return fetch("/config", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({
      profile: {
        active: profile,
      },
    }),
  });
}
