# <center> How to use Google Drive with TYSS </center>

These steps create your own Google Drive OAuth credentials and a refresh token for TYSS.

**Never share `drive.json`. Never commit real client secrets or refresh tokens.**

1. Go to https://console.cloud.google.com/ and create or select a project for TYSS.
2. Go to `APIs and Services`, then `Library`.
3. Search for `Google Drive API` and enable it.
4. Open `Google Auth Platform` or `OAuth consent screen`.
5. Configure the OAuth consent screen. For personal use, fill in the required app name, user support email, and developer contact email.
6. Add the Drive scope:

    ```
    https://www.googleapis.com/auth/drive
    ```

7. If your OAuth app remains `External` and `Testing`, Google may expire refresh tokens for the Drive scope after 7 days. For personal use, publish the app to `In production` to avoid the testing-mode token expiry when Google allows it. Because the Drive scope may be sensitive or restricted, Google may still show an unverified app warning or require app verification.
8. Go to `APIs and Services`, then `Credentials`.
9. Click `+ CREATE CREDENTIALS`, then `OAuth client ID`.
10. Set `Application type` to `Web application`. Do not use `Desktop app`.
11. Add this exact `Authorized redirect URI`:

    ```
    https://developers.google.com/oauthplayground
    ```

12. Create the client and copy the Web OAuth client ID and client secret. Because `drive.json` is stored on the SD card, do not treat this client secret as confidential after copying it there.
13. Open https://developers.google.com/oauthplayground.
14. Click the gear icon and use these settings:
    - `OAuth flow`: `Server-side`
    - `Access type`: `Offline`
    - `Force prompt`: `Consent Screen`
    - Enable `Use your own OAuth credentials`
    - Enter the Web OAuth client ID and client secret from Google Cloud
15. In the scope box, enter:

    ```
    https://www.googleapis.com/auth/drive
    ```

16. Click `Authorize APIs` and sign in with the Google account you want TYSS to use.
17. Click `Exchange authorization code for tokens`.
18. Copy the `Refresh token`.
19. On your 3DS's SD card, go to `SDMC:/TYSS`. Create a file named `drive.json`.
20. Add these lines and save:

    ```
    {
        "driveClientID": "YOUR_WEB_CLIENT_ID_HERE",
        "driveClientSecret": "YOUR_WEB_CLIENT_SECRET_HERE",
        "driveRefreshToken": "YOUR_REFRESH_TOKEN_HERE",
        "driveInitOnBoot": true
    }
    ```

Do not include `driveAuthCode` when using this method.

`driveInitOnBoot` controls whether TYSS initializes Google Drive when TYSS starts and `drive.json` exists. If this key is omitted, the current default is `true`. Set it to `false` if you do not want Drive to initialize on startup.

If `drive.json` is exposed, revoke the app's access from your Google Account, rotate the Web OAuth client secret in Google Cloud, and generate a new refresh token. Refresh tokens can also become invalid if you revoke app access, the token is unused for a long time, or too many refresh tokens are generated.

## Troubleshooting

- `invalid_client` usually means the client ID or client secret is wrong, the OAuth client was deleted, you are using the wrong Google Cloud project, or the client is not a `Web application` client.
- `redirect_uri_mismatch` means `https://developers.google.com/oauthplayground` was not added exactly as an `Authorized redirect URI`.
