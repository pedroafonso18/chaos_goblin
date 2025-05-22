# Chaos Goblin

Chaos Goblin is a chaos engineering tool inspired by Netflix's Chaos Monkey, designed to improve system resilience by deliberately introducing controlled failures and attacks.

## Overview

Chaos engineering is the practice of intentionally introducing controlled failures to identify weaknesses in systems before they cause real outages. Chaos Goblin helps you:

- Test your infrastructure's resilience
- Identify single points of failure
- Improve recovery procedures
- Build more robust applications

## Features

### Current Features
- **Infrastructure targeting**: Test resilience of databases and virtual machines
- **Safety mode**: Run simulations without causing actual damage
- **Environment separation**: Target testing or production environments selectively
- **Scheduled chaos**: Configure runs via crontab
- **Docker integration**: Target containerized applications

### Planned Features
- **Web application testing**: Controlled attacks on websites and APIs (with explicit permission)
- **Comprehensive security testing**: Continuous penetration testing to strengthen defenses
- **API key authentication**: Secure permission system for testing external systems
- **Advanced reporting**: Detailed analysis of system resilience

## Configuration

Chaos Goblin uses a TOML configuration file (`goblin.toml`) for all settings:

```toml
[goblin]
enabled = true          # Enable/disable the goblin
is_scheduled = true     # Use crontab scheduling
is_safe = true          # Simulation mode (no actual damage)
level = "testing"       # Target environment level
crontab = "* * * *"     # Schedule for chaos events

# Database and machine configurations...
```

## Usage

[Coming soon]

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Copyright (c) 2025 Pedro Afonso