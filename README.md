# C-Project-SEM-1
Our Endsem project for C

## About This Project
This is a Supermarket Management System built in C that uses linked lists for data management and file I/O for persistence.

## How to Share This Private Repository with Friends

Since this is a private repository, you'll need to explicitly add collaborators to allow your friends to contribute. Here are the steps:

### Method 1: Adding Collaborators (Recommended for Small Teams)

#### For Repository Owner:

1. **Navigate to Repository Settings**
   - Go to your repository on GitHub: `https://github.com/PotatousNoobus/C-Project-SEM-1`
   - Click on the **Settings** tab (you need admin access)

2. **Access Collaborators Section**
   - In the left sidebar, click on **Collaborators and teams** (or just **Collaborators**)
   - You may need to confirm your password for security

3. **Add Collaborators**
   - Click the **Add people** button
   - Search for your friends by their GitHub username, full name, or email
   - Select the correct person from the search results
   - Click **Add [username] to this repository**

4. **Set Permission Level**
   - Choose the appropriate permission level:
     - **Read**: Can view and clone the repository
     - **Write**: Can push to the repository (recommended for contributors)
     - **Admin**: Full control including settings (use sparingly)
   - For contributors, **Write** access is typically appropriate

#### For Your Friends (Collaborators):

1. **Accept the Invitation**
   - Your friend will receive an email invitation from GitHub
   - They should click the link in the email, or
   - Visit `https://github.com/PotatousNoobus/C-Project-SEM-1` and accept the invitation banner at the top

2. **Clone the Repository**
   ```bash
   git clone https://github.com/PotatousNoobus/C-Project-SEM-1.git
   cd C-Project-SEM-1
   ```

3. **Start Contributing**
   - Create a new branch for their work:
     ```bash
     git checkout -b feature-name
     ```
   - Make changes, commit, and push:
     ```bash
     git add .
     git commit -m "Description of changes"
     git push origin feature-name
     ```
   - Open a Pull Request on GitHub to merge changes

### Method 2: Using a GitHub Organization (For Larger Teams)

If you have multiple projects or a larger team:

1. Create a GitHub Organization (free for open source/education)
2. Transfer the repository to the organization
3. Add team members to the organization
4. Manage access through teams with different permission levels

### Method 3: Fork and Pull Request (For External Contributors)

For contributors without direct write access:

1. They fork the repository to their account
2. Clone their fork and make changes
3. Push changes to their fork
4. Submit a Pull Request to your repository

### Best Practices for Collaboration

1. **Use Branches**: Always create a new branch for features or fixes
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Pull Before You Push**: Always pull the latest changes before starting work
   ```bash
   git pull origin main
   ```

3. **Write Clear Commit Messages**: Describe what and why
   ```bash
   git commit -m "Add customer purchase validation"
   ```

4. **Use Pull Requests**: Don't push directly to main; use PRs for code review

5. **Communicate**: Discuss major changes in issues before implementing

### Project Setup for Contributors

#### Prerequisites
- GCC compiler installed
- Git installed
- A GitHub account

#### Building the Project
```bash
gcc main.c crud.c -o supermarket
```

#### Running the Application
```bash
./supermarket
```

### Troubleshooting

**Problem**: Friend can't see the repository
- **Solution**: Make sure you added them as a collaborator and they accepted the invitation

**Problem**: Friend gets "Permission denied" when pushing
- **Solution**: Verify they have Write access (not just Read)

**Problem**: Can't find the "Add people" button
- **Solution**: You need to be the repository owner or have admin access

### Need Help?

If you have questions about collaborating on this project, please open an issue or contact the repository owner.
