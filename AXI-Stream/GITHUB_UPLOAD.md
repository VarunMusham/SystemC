# GitHub Upload Instructions

## Step-by-Step Guide to Upload to GitHub

### Step 1: Create Repository on GitHub

1. Go to https://github.com/new
2. **Repository name**: `axi4-stream-tlm-lt` (or your preferred name)
3. **Description**: `User-friendly AXI4-Stream protocol implementation using SystemC TLM Loosely-Timed model`
4. **Public**: Select (so others can use it)
5. **Add .gitignore**: Skip (we have one already)
6. **Add license**: Skip (we have MIT license)
7. Click **"Create repository"**

### Step 2: Get Your Repository URL

After creating, GitHub shows you commands. You need your repository URL:

```
https://github.com/YOUR-USERNAME/axi4-stream-tlm-lt.git
```

Or if using SSH:
```
git@github.com:YOUR-USERNAME/axi4-stream-tlm-lt.git
```

### Step 3: Add Remote and Push

Open PowerShell in the AXI-Stream folder:

```powershell
cd d:\Programming\SystemC\AXI-Stream
```

Add the remote repository:

```powershell
git remote add origin https://github.com/YOUR-USERNAME/axi4-stream-tlm-lt.git
```

Replace:
- `YOUR-USERNAME` with your GitHub username
- `axi4-stream-tlm-lt` with your chosen repository name

### Step 4: Push to GitHub

```powershell
git branch -M main
git push -u origin main
```

This:
- Renames current branch to `main`
- Pushes all commits to GitHub
- Sets `main` as default branch

### Step 5: Verify Upload

1. Go to https://github.com/YOUR-USERNAME/axi4-stream-tlm-lt
2. You should see all files
3. README.md will be displayed as homepage

## Expected Output

```powershell
PS D:\Programming\SystemC\AXI-Stream> git branch -M main
PS D:\Programming\SystemC\AXI-Stream> git push -u origin main
Enumerating objects: 16, done.
Counting objects: 100% (16/16), done.
Delta compression using up to 8 threads
Compressing objects: 100% (13/13), done.
Writing objects: 100% (16/16), 45.23 KiB | 1.23 MiB/s, done.
Total 16 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/YOUR-USERNAME/axi4-stream-tlm-lt.git
 * [new branch]      main -> main
branch 'main' set to track 'origin/main'.
```

## Using SSH Instead (Optional - More Secure)

If you prefer SSH and have it configured:

```powershell
git remote set-url origin git@github.com:YOUR-USERNAME/axi4-stream-tlm-lt.git
git push -u origin main
```

## After Upload

### For Sharing

Share this link:
```
https://github.com/YOUR-USERNAME/axi4-stream-tlm-lt
```

### Adding Files Later

If you make changes:

```powershell
cd d:\Programming\SystemC\AXI-Stream
git add .                          # Stage all changes
git commit -m "Your change message"
git push                           # Push to GitHub
```

### Common Commands After Upload

```powershell
git pull              # Get latest from GitHub
git status            # See what changed
git log               # See commit history
git diff              # See specific changes
```

## Troubleshooting

### "fatal: 'origin' does not appear to be a 'git' repository"

Your remote wasn't added properly.

**Solution:**
```powershell
git remote -v                  # Check remotes
git remote remove origin       # Remove bad one
git remote add origin <URL>    # Add correct one
git push -u origin main        # Try again
```

### "fatal: could not read Username"

Need to authenticate.

**Solutions:**
- Use **Personal Access Token** (GitHub recommends this)
- Or configure SSH key
- Or use GitHub Desktop

### "Updates were rejected"

Remote has different history.

**Solution** (be careful with this):
```powershell
git push -u origin main --force
```

### Authentication Problems

**Using HTTPS + Token:**
1. Generate token: https://github.com/settings/tokens
2. When prompted for password, paste the token

**Using SSH:**
1. Generate key: `ssh-keygen -t ed25519 -C "your-email@example.com"`
2. Add public key to GitHub: https://github.com/settings/keys

## Repository Topics

After upload, add topics for discoverability:

1. Go to repository Settings
2. Scroll to "Repository topics"
3. Add tags:
   - `axi4-stream`
   - `systemc`
   - `tlm`
   - `loosely-timed`
   - `hardware-simulation`
   - `verilog-alternative`

## Repository Description

Edit description to:
```
AXI4-Stream TLM LT protocol implementation in SystemC. 
Beginner-friendly with examples and comprehensive documentation.
```

## Next: Create GitHub Pages Documentation

Optional: Add GitHub Pages for better documentation.

1. Settings → Pages
2. Select main branch
3. Folder: root or docs/
4. Your README automatically becomes the page

## Making It Discovery-Friendly

To help others find your project:

1. ✅ Add descriptive README.md (done)
2. ✅ Add topics/tags (do this)
3. ✅ Add LICENSE (done - MIT)
4. ✅ Add .gitignore (done)
5. ✅ Keep code clean and organized (done)
6. ⭐ Encourage stars: Add instruction in README

## Example README Update for GitHub

Add to top of README.md:

```markdown
# AXI4-Stream TLM LT

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A user-friendly implementation of AXI4-Stream protocol using SystemC TLM Loosely-Timed model.

**Perfect for learning** • **Zero comments** • **Beginner-friendly**

⭐ If this helps you, please star the repo!
```

## Quick Reference

| Task | Command |
|------|---------|
| Check status | `git status` |
| See changes | `git diff` |
| Commit | `git commit -m "message"` |
| Push | `git push` |
| Pull | `git pull` |
| View history | `git log --oneline` |
| Undo change | `git checkout -- filename` |

## Share with Others

Once uploaded:

1. **Direct link**: `https://github.com/YOUR-USERNAME/axi4-stream-tlm-lt`
2. **In emails**: Share the link
3. **In documentation**: Reference your repo
4. **On social media**: Share with `#systemc #hardware #simulation`

## Continuous Updates

Create new commits for improvements:

```powershell
# After making changes
git add .
git commit -m "Descriptive message about what changed"
git push
```

Keep repository active with commits for better visibility.

## Summary

You now have:
- ✅ Local Git repository
- ✅ All AXI4-Stream implementation
- ✅ 3 working examples
- ✅ Complete documentation
- ✅ MIT License
- ✅ Ready to push to GitHub

**Final step**: Follow Step 1-4 above to upload!

---

**Questions?** Check GitHub Help: https://docs.github.com/
